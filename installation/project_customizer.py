import os
import re
import Tkinter as tk
from functools import partial
from shutil import copyfile
import sys

class ScrollableFrame(tk.Frame):
    def __init__(self, master, **kwargs):
        tk.Frame.__init__(self, master, **kwargs)

        # create a canvas object and a vertical scrollbar for scrolling it
        self.vscrollbarV = tk.Scrollbar(self, orient=tk.VERTICAL)

        self.vscrollbarV.pack(side='right', fill="y",  expand="false")
        self.canvas = tk.Canvas(self,
                                bg='#cecece', bd=0,
                                height=650,
                                highlightthickness=0,
                                yscrollcommand=self.vscrollbarV.set
                                )
        
        self.canvas.pack(side="bottom", fill="both", expand="false")
        self.vscrollbarV.config(command=self.canvas.yview)
        
        # reset the view
        self.canvas.xview_moveto(0)
        self.canvas.yview_moveto(0)
        self.domains = []
        # create a frame inside the canvas which will be scrolled with it
        self.interior = tk.Frame(self.canvas, **kwargs)
        
        self.canvas.create_window(0, 0, window=self.interior, anchor="nw")
        
        self.bind('<Configure>', self.set_scrollregion)
        self.labels = []
        
        self.text = tk.StringVar()
        self.text.set("")
        self.label = tk.Label(self, textvariable=self.text, bg='#eeeeee', width = 80, anchor='n', highlightthickness=1, highlightbackground="#999999")
        self.label.pack(expand="false")
    
        
    def set_scrollregion(self, event=None):
        """ Set the scroll region on the canvas"""
        
        self.canvas.configure(scrollregion=self.canvas.bbox('all'))
        
    def change_label(self, title):
        """ Set the label of the frame """    
        self.text.set(title)
        
    def get_text_label(self):
        return self.text.get()
    
    def create_domain(self, **kwargs):
        self.domains.append(tk.Frame(self.canvas, **kwargs))
        
    def change_domain(self, index):
        self.interior = self.domains[index]
        self.canvas.delete("all")
        self.canvas.create_window(0, 0, window=self.interior, anchor="nw")
    
class ToolTip(object):

    def __init__(self, widget):
        self.widget = widget
        self.tipwindow = None
        self.id = None
        self.x = self.y = 0

    def showtip(self, text):
        "Display text in tooltip window"
        self.text = text
        if self.tipwindow or not self.text:
            return
        x, y, cx, cy = self.widget.bbox("insert")
        x = x + self.widget.winfo_rootx() + 57
        y = y + cy + self.widget.winfo_rooty() +27
        self.tipwindow = tw = tk.Toplevel(self.widget)
        tw.wm_overrideredirect(1)
        tw.wm_geometry("+%d+%d" % (x, y))
        label = tk.Label(tw, text=self.text, justify="left",
                      background="#ffffe0", relief="solid", borderwidth=1,
                      font=("tahoma", "8", "normal"))
        label.pack(ipadx=1)

    def hidetip(self):
        tw = self.tipwindow
        self.tipwindow = None
        if tw:
            tw.destroy()

# create a label with text when pointer over the widget
def CreateToolTip(widget, text):
    toolTip = ToolTip(widget)
    def enter(event):
        toolTip.showtip(text)
    def leave(event):
        toolTip.hidetip()
    widget.bind('<Enter>', enter)
    widget.bind('<Leave>', leave)


def get_initial_project_modules():

    initial_submodules = []

    try:
        with open(GITMODULES_ROOTDIR + PROJECT_CONFIG + "project_modules.txt", 'rb') as f:
            # Read lines
            gt_list = f.readlines()
            for i in range(len(gt_list)):
                if gt_list[i].startswith("[submodule"):
                    path = re.findall(r'"(.*?)"', gt_list[i])[0]
                    initial_submodules.append(os.path.split(path)[1])
                # Configure the selected head point

    except IOError:
        pass

    return initial_submodules
       
def get_git_modules(p_modules):
    
    print("INFO: Press Save to update selected modules...")
    
    try:         
        with open(GITMODULES_ROOTDIR + '.gitmodules', 'rb') as f:            
        # Read lines
            gt_list = f.readlines()
            
            for i in range(len(gt_list)):
                
                if gt_list[i].startswith("[submodule"):
                # Find name of the submodule and activate prior activation for this project
                    current_path = gt_list[i + 1].split(' ')
                    path1 = os.path.split(current_path[2])[0].replace('\n', '')
                    # curent module                    
                    current_module = os.path.split(current_path[2])[1].replace('\n', '')                   
                   

                    if not path1 in path_first:
                        path_first.append(path1)
                        b = tk.IntVar()                 
                        var_first.append(b)
                        var_first[len(var_first)-1].set(0)
                        p,v,c = [],[],[]
                        path_last.append(p)
                        var_last.append(v)
                        path_complete.append(c)
                                              
                    for j in range(len(path_first)):
                        if path_first[j] == path1:
                            path_last[j].append(current_module)
                            a = tk.IntVar()
                            var_last[j].append(a)
                            var_last[j][len(var_last[j])-1].set(0)
                            path_complete[j].append(current_path[2])
                            if len(p_modules) > 0 and current_module in p_modules:          
                                # Activate those that where present
                                var_last[j][len(var_last[j])-1].set(1)
                         
    except IOError:
        pass
    
    return path_first, path_last, var_first, var_last, gt_list, path_complete

def ask_confirmation():
    
    emergent_window = tk.Toplevel()
    emergent_window.grab_set()
    emergent_window.attributes("-topmost", True)
    
    emergent_window.title("Project selector")
    emergent_window.configure(width = 350, height = 150, background= "#d9d9d9")
    emergent_window.resizable(False, False)
    x = root.winfo_x()
    y = root.winfo_y()
    emergent_window.geometry("+%d+%d" % (x + 200, y + 100))
    
    tk.Label(emergent_window , text="Do you want to save the changes you made to :"+ '\n' + PROJECT_CONFIG + "?", bg='#d9d9d9', width = 50, height = 6, anchor = 'center', font=("Courier", 11)).grid(row = 0, column=0,pady = 2, sticky = 'n')
    tk.Button(emergent_window, text = "Save", bd=0, width=8, height=1, activeforeground="blue", cursor='hand1', relief='solid',bg= '#cecece', highlightthickness=1, highlightbackground="#999999", command= lambda:[emergent_window.destroy(),save_exit(1)]).grid(row = 1, column = 0, sticky = 'e', padx=10, pady=8)
    tk.Button(emergent_window, text = "Cancel", bd=0, width=8,height=1, activeforeground="blue", cursor='hand1', relief='solid',bg= '#cecece', highlightthickness=1, highlightbackground="#999999", command = emergent_window.destroy).grid(row = 1, column = 0, sticky = 's', padx=10, pady=8)
    tk.Button(emergent_window, text = "Don't save", bd=0, width=8,height=1, activeforeground="blue", cursor='hand1', relief='solid',bg= '#cecece', highlightthickness=1, highlightbackground="#999999", command = root.quit).grid(row = 1, column = 0, sticky = 'w', padx= 10, pady=8 )

def save_exit (flag):
    var_selector()
    window = tk.Toplevel()
    window.attributes("-topmost", True)
    window.grab_set()
    window.title("Project selector")
    window.configure(width = 150, height = 75, background= "#d9d9d9")
    window.resizable(False, False)
    x = root.winfo_x()
    y = root.winfo_y()
     
    window.geometry("+%d+%d" % (x + 200, y + 100))
    tk.Label(window , text=PROJECT_CONFIG + ": " + "\n" + "Succesfully saved.", bg='#d9d9d9', width = 40, height = 6, anchor = 'center',font=("Courier", 11)).grid(row = 0, column=0,pady = 2, sticky = 'n')
 
    if flag == 0:
        tk.Button(window, text = "OK", bd=0, width=7,height=1, activeforeground="blue", cursor='hand1', relief='flat',bg= '#cecece', highlightthickness=1, highlightbackground="#999999", command= window.destroy).grid(row = 1, column = 0, sticky = 'e', padx=10, pady=8)
    else:
        window.protocol("WM_DELETE_WINDOW", Quit)
        tk.Button(window, text = "OK", bd=0, width=7,height=1, activeforeground="blue", cursor='hand1', relief='flat',bg= '#cecece', highlightthickness=1, highlightbackground="#999999", command= Quit).grid(row = 1, column = 0, sticky = 'e', padx=10, pady=8)

def refresh_modules():
        # Try removing previous generated file     
        try: 
            os.makedirs(GITMODULES_ROOTDIR + PROJECT_CONFIG)
            print("INFO: Created project directory: " + GITMODULES_ROOTDIR + PROJECT_CONFIG)
        except OSError:
            if not os.path.isdir(GITMODULES_ROOTDIR + PROJECT_CONFIG):
                raise
        try:
            os.remove(GITMODULES_ROOTDIR + PROJECT_CONFIG + 'project_modules.txt')
            print("INFO: Removing previous generated files if they exist...")
        except:
            pass

def Reset():
    initial_submodules = get_initial_project_modules()
    
    for i, modules_list in enumerate(path_last):
        for j, module in enumerate(modules_list):
            var_last[i][j].set(0)
            if module in initial_submodules:
                var_last[i][j].set(1)
        checkMainButton(i)
        
def Quit():
    initial_submodules = get_initial_project_modules()
    boolean = 0
    for i, modules_list in enumerate(path_last):
        for j, module in enumerate(modules_list):
            
            if module in initial_submodules:
                if var_last[i][j].get() == 0:
                    boolean = 1
                    ask_confirmation()
                    break
            else:
                if var_last[i][j].get() == 1:
                    boolean = 1
                    ask_confirmation()
                    break
        if boolean ==1:
            break
        
    if boolean == 0:       
        root.quit()
          
        
def var_selector():
        refresh_modules()
              
        for j in range(len(gt_list)):
            if gt_list[j].startswith("[submodule"):
                i = 1
                path = re.findall(r'"(.*?)"', gt_list[j])[0] 
                module = os.path.split(path)[1]
                
                for group in range(len(path_last)):
                    for index in range(len(path_last[group])):
                        if path_last[group][index] == module:
                            val = var_last[group][index].get()                                    
                if val == 1:
                        # Include file in new project_modules.txt
                    try: 
                        with open(GITMODULES_ROOTDIR + PROJECT_CONFIG + 'project_modules.txt', 'a') as f:
                            f.write(gt_list[j])
                          
                            while not gt_list[j + i].startswith("[submodule"):
                                f.write(gt_list[j+i])                                
                                i += 1                                
                    except:
                        pass
                    
def clear(frame):
    list = frame.grid_slaves()
    for l in list:
        l.destroy()

def checkMainButton(index):
    suma = 0
    for j in var_last[index]:
        suma += j.get()
                      
    if suma == len(var_last[index]):
        var_first[index].set(1)       
    elif suma == 0:
        var_first[index].set(0)
    else:
        var_first[index].set(2)
                      
def ChangeDomain(module, index, mode, frame, main_frame):
        if mode == "check":
            
            if var_first[index].get() == 1:
                for j in range(len(var_last[index])):
                    var_last[index][j].set(1)
                       
            else:
                for j in range(len(var_last[index])):
                    var_last[index][j].set(0)               
        
        if module != frame.get_text_label():                         
                    
            frame.change_label(module)                        
            frame.change_domain(index)    
            frame.set_scrollregion(frame.domains[index])
            buttons = main_frame.interior.grid_slaves()
            for i, button in enumerate(buttons):
                if(button.cget('fg') == 'blue'):
                    button.config(fg='black')
            main_frame.interior.grid_slaves(index+1, 1)[0].config(fg='blue')
            
        
def generate_main_window():
    root.title(os.path.split(PROJECT_CONFIG)[0] + ": Project selector")
    root.config(menu=menu,bg='#d9d9d9',highlightbackground="#a9a9a9")
    root.resizable(False, False)
    parameter = ""
    subMenu = tk.Menu(menu, tearoff=0)
    
    menu.add_cascade(label="File", menu=subMenu)
    subMenu.add_command(label="Save", command=partial(save_exit, 0))
    subMenu.add_command(label="Reset", command=Reset)
    subMenu.add_separator()
    subMenu.add_command(label="Exit", command=Quit)
    root.protocol("WM_DELETE_WINDOW", Quit)

    helpMenu = tk.Menu(menu)
    menu.add_cascade(label="Help", menu = helpMenu)
    frameLeft = tk.Frame(root, bg='#d9d9d9', borderwidth = 0, highlightbackground="#a9a9a9", highlightthickness=0)
    frameLeft.pack(side = "left", expand="true", fill="both")
    checkboxLeft = ScrollableFrame(frameLeft, bg='#d9d9d9', borderwidth = 0, highlightbackground="#a9a9a9", highlightthickness=2)
    checkboxLeft.pack(expand="true", fill="both")
    checkboxLeft.change_label("Choose a main domain")
     
    frameRight = tk.Frame(root, bg='#d9d9d9', borderwidth = 0, highlightbackground="#a9a9a9", highlightthickness=0)
    frameRight.pack(side = "right", expand="true", fill="both")
    checkboxRight = ScrollableFrame(frameRight, bg='#d9d9d9', borderwidth = 0, highlightbackground="#a9a9a9", highlightthickness=2)
    checkboxRight.change_label("...")
    for i, module_list in enumerate(path_last):
               
        tk.Checkbutton(checkboxLeft.interior, bd=3, bg= '#d9d9d9',anchor = 'w', highlightthickness=0, variable = var_first[i], tristatevalue=2, command=partial(ChangeDomain,path_first[i].replace('\n', ''), i, "check", checkboxRight, checkboxLeft)).grid(row=i+1, column = 0, sticky='w', pady = 3)     
        button = tk.Button(checkboxLeft.interior, text = path_first[i].replace('\n', ''), bd=1, width = 80, activeforeground="#00067c", cursor='hand1', relief='flat',bg= '#d9d9d9', anchor='w', highlightthickness=0, command= partial(ChangeDomain,path_first[i].replace('\n', ''), i, "select", checkboxRight, checkboxLeft))
        button.grid(row=i+1, column = 1, pady = 3)         
        checkMainButton(i)
        print("Domain: "+path_first[i].replace('\n', '') + " loaded ")
        checkboxRight.create_domain(bg='#d9d9d9', borderwidth = 0, highlightbackground="#a9a9a9", highlightthickness=2)        
        for j, submodule in enumerate(path_last[i]):
            print ("   " + "module: " + submodule + " loaded" + '\n')               
            button = tk.Checkbutton(checkboxRight.domains[i], text=submodule, bg= '#d9d9d9', width=80, anchor='w', bd= 6, justify='left', highlightthickness=0, command = partial(checkMainButton, i), variable=var_last[i][j])
            CreateToolTip(button, text = path_complete[i][j])
            button.grid(row=j+1, sticky='s', pady=1) 
                    
    checkboxRight.pack(expand="true", fill="both")                    

if __name__ == '__main__':

    active_frame = ""
    if len(sys.argv) < 3:
        print("ERROR: Correct syntax: 'python aerostack_project_selector.py <root_aerostack_path> <project_folder>'")
        exit()
        
    if (len(sys.argv)>3 and sys.argv[3]=="-c"):
        configure=1
    
    GITMODULES_ROOTDIR = sys.argv[1]
    PROJECT_CONFIG = sys.argv[2]
        
    print("INFO: Project directory: "+ GITMODULES_ROOTDIR + PROJECT_CONFIG)

    print("INFO: Retrieving previous configuration if it exists...")

    print("INFO: Reading submodules info...")
    root = tk.Tk()
    menu = tk.Menu(root)
    # path_first: List of supermodules; path_last: List of module's Lists; var_first: List of IntVar representing supermodules state;
    # var_last: List of IntVar Lists representing each module state; path_complete: List of each modules' path Lists;  
    path_first, path_last, var_first, var_last, gt_list, path_complete = [],[],[],[],[],[]
    
    initial_submodules = get_initial_project_modules()

    path_first, path_last, var_first, var_last, gt_list, path_complete = get_git_modules(initial_submodules)
    
    generate_main_window()
    
    print("loading...")
    root.mainloop()
    
    
    



