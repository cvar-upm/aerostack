"""aerostack_project_selector.py: Configures the Aerostack framework for different project configurations"""

__author__      = "Alejandro Rodriguez-Ramos"
__email__       = "alejandro.rramos@upm.es"

import os
import re
import Tkinter as tk
from shutil import copyfile
import sys

class ScrollableFrame(tk.Frame):
    def __init__(self, master, **kwargs):
        tk.Frame.__init__(self, master, **kwargs)

        # create a canvas object and a vertical scrollbar for scrolling it
        self.vscrollbar = tk.Scrollbar(self, orient=tk.VERTICAL)
        self.vscrollbar.pack(side='right', fill="y",  expand="false")
        self.canvas = tk.Canvas(self,
                                bg='#444444', bd=0,
                                height=650,
                                highlightthickness=0,
                                yscrollcommand=self.vscrollbar.set)
        self.canvas.pack(side="left", fill="both", expand="true")
        self.vscrollbar.config(command=self.canvas.yview)

        # reset the view
        self.canvas.xview_moveto(0)
        self.canvas.yview_moveto(0)

        # create a frame inside the canvas which will be scrolled with it
        self.interior = tk.Frame(self.canvas, **kwargs)
        self.canvas.create_window(0, 0, window=self.interior, anchor="nw")

        self.bind('<Configure>', self.set_scrollregion)


    def set_scrollregion(self, event=None):
        """ Set the scroll region on the canvas"""
        self.canvas.configure(scrollregion=self.canvas.bbox('all'))


if __name__ == '__main__':
    # Read arguments
    if len(sys.argv) < 3:
        print("Correct syntax: 'python aerostack_project_selector.py <root_aerostack_path> <project_folder>'")
        exit()

    root = tk.Tk()
    checkbox_pane = ScrollableFrame(root, bg='#444444')
    checkbox_pane.pack(expand="true", fill="both")

    # Get submodules list
    GITMODULES_ROOTDIR = sys.argv[1]
    PROJECT_CONFIG = sys.argv[2]

    # Make a .gitmodules backup
    copyfile(GITMODULES_ROOTDIR + ".gitmodules", GITMODULES_ROOTDIR + PROJECT_CONFIG + ".gitmodules_backup")
    print("INFO: Backup of .gitmodules has been created (.gitmodules_backup)")

    # Include CATKIN_IGNORE in every repository
    # for subdir, dirs, files in os.walk(GITMODULES_ROOTDIR):
    #     for file in files:
    #         if file == ".git":
    #             print("Found .git: " + str(os.path.join(subdir, file)))
    #             try:
    #                 open(os.path.join(subdir, "CATKIN_IGNORE"), 'a').close()
    #             except:
    #                 pass

    # If previous configuration is defined
    prior_submodules = []
    try:
        with open(GITMODULES_ROOTDIR + PROJECT_CONFIG + ".gitmodules", 'rb') as f:
            # Read lines
            gt_list = f.readlines()
            prior_paths = []
            for i, row in enumerate(gt_list):
                if row.startswith("[submodule"):
                    current_path = re.findall(r'"(.*?)"', row)[0]
                    prior_submodules.append(os.path.split(current_path)[1])
                    current_path = gt_list[i + 1].split(' ')
                    prior_paths.append(current_path[2].replace('\n', ''))
    except:
        pass

    with open(GITMODULES_ROOTDIR + '.gitmodules', 'rb') as f:
        # Read lines
        gt_list = f.readlines()
        paths = []
        submodules = []
        prior_var = []
        for i, row in enumerate(gt_list):
            if row.startswith("[submodule"):
                current_path = re.findall(r'"(.*?)"', row)[0]
                current_submodule = os.path.split(current_path)[1]
                submodules.append(current_submodule)
                prior_var.append(0)
                current_path = gt_list[i + 1].split(' ')
                paths.append(current_path[2].replace('\n', ''))
                if len(prior_submodules) > 0:
                    for prior_submodule in prior_submodules:
                        if prior_submodule == current_submodule:
                            prior_var[len(prior_var) - 1] = 1


    def var_states():
        # Remove all the CATKIN_IGNORE found
        for subdir, dirs, files in os.walk(GITMODULES_ROOTDIR):
            for file in files:
                if file == "CATKIN_IGNORE":
                    # print("Found CATKIN_IGNORE: " + str(os.path.join(subdir, file)))
                    try:
                        os.remove(os.path.join(subdir, file))
                    except:
                        pass

        # Try removing previous generated file
        try:
            os.remove(GITMODULES_ROOTDIR + PROJECT_CONFIG + '.gitmodules')
        except:
            pass

        try:
            os.remove(GITMODULES_ROOTDIR + PROJECT_CONFIG + 'git_submodule_sequence.sh')
        except:
            pass

        try:
            os.remove(GITMODULES_ROOTDIR + 'git_submodule_sequence.sh')
        except:
            pass

        with open(GITMODULES_ROOTDIR + '.gitmodules', 'rb') as f:
            # Read lines
            gt_list = f.readlines()
            k = 0
            for j, line in enumerate(gt_list):
                if gt_list[j].startswith("[submodule"):
                    k = k + 1

                    # Add CATKIN_IGNORE
                    try:
                        # print(os.path.join(GITMODULES_ROOTDIR, paths[k - 1] + "/CATKIN_IGNORE"))
                        os.mknod(os.path.join(GITMODULES_ROOTDIR, paths[k - 1] + "/CATKIN_IGNORE"))
                    except:
                        print("File already exists: " + os.path.join(GITMODULES_ROOTDIR, paths[k - 1] + "/CATKIN_IGNORE"))

                    if var_list[k - 1].get() == 1:
                        # Include file in new .gitmodules
                        with open(GITMODULES_ROOTDIR + PROJECT_CONFIG + '.gitmodules', 'a') as the_file:
                            the_file.write(gt_list[j])
                        try:
                            if "path = " in gt_list[j + 1]:
                                # print(gt_list[j + 1])
                                with open(GITMODULES_ROOTDIR + PROJECT_CONFIG + '.gitmodules', 'a') as the_file:
                                    the_file.write(gt_list[j + 1])
                            if "url = " in gt_list[j + 2]:
                                # print(gt_list[j + 2])
                                with open(GITMODULES_ROOTDIR + PROJECT_CONFIG + '.gitmodules', 'a') as the_file:
                                    the_file.write(gt_list[j + 2])
                            if "branch = " in gt_list[j + 3]:
                                # print(gt_list[j + 3])
                                with open(GITMODULES_ROOTDIR + PROJECT_CONFIG + '.gitmodules', 'a') as the_file:
                                    the_file.write(gt_list[j + 3])
                        except:
                            pass

                        # Include in output script
                        with open(GITMODULES_ROOTDIR + PROJECT_CONFIG + 'git_submodule_sequence.sh', 'a') as the_file:
                            the_file.write("git submodule update --init " + paths[k - 1] + "\n")

                        # Remove previously included CATKIN_IGNORE
                        os.remove(os.path.join(GITMODULES_ROOTDIR, paths[k - 1] + "/CATKIN_IGNORE"))

        # Copy script to aerostack root
        copyfile(GITMODULES_ROOTDIR + PROJECT_CONFIG + "git_submodule_sequence.sh",
                 GITMODULES_ROOTDIR + "git_submodule_sequence.sh")

        print("INFO: All modules but selected have been put into CATKIN_IGNORE")
        print("INFO: Please, proceed to execute gitsubmodule_sequence.sh to update selected submodules")
        print("INFO: Process executed successfully")



    var_list = []

    for i, submodule in enumerate(submodules):
        var_list.append(tk.IntVar())
        var_list[i].set(prior_var[i])
        tk.Checkbutton(checkbox_pane.interior, text=submodule, variable=var_list[i]).grid(row=(i + 1), column=0)

    tk.Button(checkbox_pane.interior, text='Generate', command=var_states).grid(row=(i + 2), column=0)
    tk.Button(checkbox_pane.interior, text='Quit', command=root.quit).grid(row=(i + 3), column=0)

    root.mainloop()


