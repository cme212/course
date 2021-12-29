Here are some tips for setting up your VM that should make your life easier.

From the "Oracle VM VirtualBox Manager" menu, select the cme212-ubuntu-vm in the RHS panel, and then open the "Settings" menu.

1.  Under "General" >> "Advanced" >> "Shared clipboard" select _Bidirectional._ This will allow you to copy/paste content between the VM and your local computer.
2.  Under "System" >> "Motherboard" >> "Base Memory" you might want to consider increasing the memory.  This could improve some of the latency issues.
3.  Under "Display" >> "Screen" >> "Video Memory", again consider increasing the memory to improve latency.
4.  If you want to share a folder between your local computer and the VM:
    *   "Shared Folder" >> + Folder icon 
        *   **Folder path:** Local path to folder, e.g. /Users/jesswetstone/
        *   Folder name: Name of local folder, e.g. cme212-jhwetstone
        *   Select Auto-mount
        *   Mount point: Name of folder on VM, e.g. cme212-jhwetstone
        *   Select Make Permanent
    *   Save settings and log on to the VM. In a terminal window, type:  
        
        ```
        sudo usermod -aG vboxsf $USER
        ```
        
    *   Log off and log back on.  Under "Files" on the VM, you should have access to the shared folder _/media/sf\_\[Mount point\]_
5.  If you would like to use the Sublime text editor on the VM: [http://tipsonubuntu.com/2017/05/30/install-sublime-text-3-ubuntu-16-04-official-way/](http://tipsonubuntu.com/2017/05/30/install-sublime-text-3-ubuntu-16-04-official-way/#prettyPhoto)

Note: If you are able to run code locally, you should probably be OK to develop locally for most of the classwork this quarter.  We recommend having a working VM configured for testing purposes and if for some reason later on in the course your code won't compile locally.
