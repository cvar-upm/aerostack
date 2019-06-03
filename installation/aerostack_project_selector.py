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
    devel=0
    if len(sys.argv) < 3:
        print("ERROR: Correct syntax: 'python aerostack_project_selector.py <root_aerostack_path> <project_folder>'")
        exit()
        
    if (len(sys.argv)>3 and sys.argv[3]=="-d"):
        devel=1
    if(devel):
        root = tk.Tk()
        checkbox_pane = ScrollableFrame(root, bg='#444444')
        checkbox_pane.pack(expand="true", fill="both")

    # Get submodules list
    GITMODULES_ROOTDIR = sys.argv[1]
    PROJECT_CONFIG = sys.argv[2]


    print("INFO: Project directory: "+ GITMODULES_ROOTDIR + PROJECT_CONFIG)

    # Make a .gitmodules backup
    copyfile(GITMODULES_ROOTDIR + ".gitmodules", GITMODULES_ROOTDIR + PROJECT_CONFIG + ".gitmodules_backup")
    print("INFO: Backup of .gitmodules has been created (.gitmodules_backup)")

    print("INFO: Retrieving previous configuration if it exists...")
    prior_submodules = []
    prior_commits = []
    prior_commits_submodule = []
    try:
        with open(GITMODULES_ROOTDIR + PROJECT_CONFIG + "project_modules.txt", 'rb') as f:
            # Read lines
            gt_list = f.readlines()
            prior_paths = []
            for i, row in enumerate(gt_list):
                if row.startswith("[submodule"):
                    current_path = re.findall(r'"(.*?)"', row)[0]
                    prior_submodules.append(os.path.split(current_path)[1])
                    current_path = gt_list[i + 1].split(' ')
                    prior_paths.append(current_path[2].replace('\n', ''))
                    # Configure the selected commit
                    try:
                        for x in range(5):
                            if "commit = " in gt_list[i + x]:
                                prior_commits.append(gt_list[i + x])
                                prior_commits_submodule.append(prior_submodules[len(prior_submodules) - 1])
                    except:
                        pass
    except:
        pass
    print("INFO: Reading submodules info...")
    with open(GITMODULES_ROOTDIR + '.gitmodules', 'rb') as f:
        # Read lines
        gt_list = f.readlines()
        paths = []
        submodules = []
        prior_var = []
        commits = []
        for i, row in enumerate(gt_list):
            if row.startswith("[submodule"):
                # Find name of the submodule and activate prior activation for this project
                current_path = re.findall(r'"(.*?)"', row)[0]
                current_submodule = os.path.split(current_path)[1]
                submodules.append(current_submodule)
                prior_var.append(0)
                current_path = gt_list[i + 1].split(' ')
                paths.append(current_path[2].replace('\n', ''))
                commits.append("")
                if len(prior_submodules) > 0:
                    # Activate those that where present
                    for prior_submodule in prior_submodules:
                        if prior_submodule == current_submodule:
                            prior_var[len(prior_var) - 1] = 1

                    # Include specific commits
                    for c, prior_submodule in enumerate(prior_commits_submodule):
                        if prior_submodule == current_submodule:
                            commits[len(commits) - 1] = prior_commits[c]
                            print("INFO: Found specific commit in module " + current_submodule + " (" + commits[len(commits) - 1] + ")")

    def var_states():
        # Remove all the CATKIN_IGNORE found
        print("INFO: Removing all CATKIN_INGNORE...")
        for subdir, dirs, files in os.walk(GITMODULES_ROOTDIR):
            for file in files:
                if file == "CATKIN_IGNORE":
                    # print("Found CATKIN_IGNORE: " + str(os.path.join(subdir, file)))
                    try:
                        os.remove(os.path.join(subdir, file))
                    except:
                        pass

        # Try removing previous generated file
        print("INFO: Removing previous generated files if they exist...")
        try:
            os.remove(GITMODULES_ROOTDIR + PROJECT_CONFIG + 'project_modules.txt')
        except:
            pass

        try:
            os.remove(GITMODULES_ROOTDIR + PROJECT_CONFIG + 'update_project_modules.sh')
        except:
            pass

        try:
            os.remove(GITMODULES_ROOTDIR + 'update_project_modules.sh')
        except:
            pass
        print("INFO: Managing CATKIN_IGNORE and creating update_project_modules.sh...")
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
                        print("INFO: File already exists: " + os.path.join(GITMODULES_ROOTDIR, paths[k - 1] + "/CATKIN_IGNORE"))
                    val=0
                    if (devel):
                        val=var_list[k - 1].get()
                    else:
                        val=var_list[k - 1]  
                    if val == 1:
                        # Include file in new project_modules.txt
                        with open(GITMODULES_ROOTDIR + PROJECT_CONFIG + 'project_modules.txt', 'a') as the_file:
                            the_file.write(gt_list[j])
                        try:
                            if "path = " in gt_list[j + 1]:
                                # print(gt_list[j + 1])
                                with open(GITMODULES_ROOTDIR + PROJECT_CONFIG + 'project_modules.txt', 'a') as the_file:
                                    the_file.write(gt_list[j + 1])
                            if "url = " in gt_list[j + 2]:
                                # print(gt_list[j + 2])
                                with open(GITMODULES_ROOTDIR + PROJECT_CONFIG + 'project_modules.txt', 'a') as the_file:
                                    the_file.write(gt_list[j + 2])
                            if "branch = " in gt_list[j + 3]:
                                # print(gt_list[j + 3])
                                with open(GITMODULES_ROOTDIR + PROJECT_CONFIG + 'project_modules.txt', 'a') as the_file:
                                    the_file.write(gt_list[j + 3])
                        except:
                            pass

                        # Include commit information
                        if commits[k - 1] != "":
                            with open(GITMODULES_ROOTDIR + PROJECT_CONFIG + 'project_modules.txt', 'a') as the_file:
                                the_file.write(commits[k - 1])

                        # Include in output script
                        with open(GITMODULES_ROOTDIR + PROJECT_CONFIG + 'update_project_modules.sh', 'a') as the_file:
                            the_file.write("git submodule update --init " + paths[k - 1] + "\n")

                        if commits[k - 1] != "":
                            current_commit = commits[k - 1].split(' ')
                            current_commit = current_commit[2].replace('\n', '')
                            with open(GITMODULES_ROOTDIR + PROJECT_CONFIG + 'update_project_modules.sh', 'a') as the_file:
                                the_file.write("cd " + paths[k - 1] + "\n")
                                the_file.write("git checkout " + current_commit + "\n")
                                the_file.write("cd -" + "\n")

                        # Remove previously included CATKIN_IGNORE
                        os.remove(os.path.join(GITMODULES_ROOTDIR, paths[k - 1] + "/CATKIN_IGNORE"))

        # Copy script to aerostack root
        copyfile(GITMODULES_ROOTDIR + PROJECT_CONFIG + "update_project_modules.sh",
                 GITMODULES_ROOTDIR + "update_project_modules.sh")

        print("INFO: All modules but selected have been put into CATKIN_IGNORE")
        print("INFO: Project set successfully")
        print("INFO: Press Quit to update selected submodules")

    var_list = []
    if(devel):
        for i, submodule in enumerate(submodules):
            var_list.append(tk.IntVar())
            var_list[i].set(prior_var[i])
            tk.Checkbutton(checkbox_pane.interior, text=submodule, variable=var_list[i]).grid(row=(i + 1), column=0)

        tk.Button(checkbox_pane.interior, text='Generate', command=var_states).grid(row=(i + 2), column=0)
        tk.Button(checkbox_pane.interior, text='Quit', command=root.quit).grid(row=(i + 3), column=0)

        root.mainloop()
    else:
        var_list =prior_var
        var_states()


