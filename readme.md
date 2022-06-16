# xfce4-winbootbutton-plugin 
`xfce4-winbootbutton-plugin` is a Xfce4 panel plugin providing a button to boot to Windows via the 
`grub-reboot <entry>` command.

## How to install 
After cloning the repository run 

    $ make

and locate your panel-plugins folders. In my case the folders can
be found at 
- `/usr/lib/xfce4/panel/plugins/` (this folder contains `.so` files)
-  `/usr/share/xfce4/panel/plugins` (this folder should contain `.desktop` files).


Copy the `libwinbootbutton.so` to the first folder 

    $ cp libwinbootbutton.so /usr/lib/xfce4/panel/plugins/

Next copy `winbootbutton.desktop` into the second folder

    $ cp winbootbutton.desktop /usr/share/xfce4/panel/plugins/
    
To make `grub-reboot` run as the root user with `sudo` from a C system call you'll need 
to add something to your `sudoers` file so `grub-reboot` can be run without a password.
I am not sure if this is the best way to do this but it works for me:

    ## Allows user '<your-username>' to use `sudo grub-reboot` without a password
    <your-username> ALL=(root) NOPASSWD: /usr/bin/grub-reboot

Add the plugin like you would any other plugin and that's it.

## No configuration yet
I want to add configuration for the boot entry which is hard-coded to `2` right now.

## Customization 
The button itself should be able to be customized with CSS although I didn't test it. Its class name is
`win-boot-button`.
