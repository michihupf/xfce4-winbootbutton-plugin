# xfce4-winbootbutton-plugin 
`xfce4-winbootbutton-plugin` is a Xfce4 panel plugin providing a button to boot to Windows via the 
`grub-reboot <entry>` command.

## How to install 
Clone the repository and run on Arch Linux:

    $ ./configure --prefix="/usr"

Other distributions need other arguments:

| Distribution | `./configure <args>`                                   |
|--------------|--------------------------------------------------------|
| Ubuntu       | `--prefix="/usr" --libdir="/usr/lib/x86_64-linux-gnu"` |
| Fedora 24    | `--prefix="/usr" --libdir="/usr/lib64"`                |
| Other        | depends on plugin folder location                      |

Install the plugin to your plugins folder by running 

    $ make
    $ sudo make install

The plugin should now show up in the `Panel Preferences` UI.

The plugin uses `sudo` to change the grub boot order by default.
This requires to add the following to your sudoers file.

    ## Allows user 'user' to use `sudo grub-reboot` without a password
    user ALL=(root) NOPASSWD: /usr/bin/grub-reboot

Alternatively one can also switch to using `pkexec` instead of `sudo`.


## Configuration
For easier use the plugin can now be configured to use `pkexec` instead of `sudo`.
This removes the need to add a no-password-policy for grub-reboot to your 
suoders file.
Just right click on the Button and click 'Properties'. Here you 
can change your boot entry as well as change if `pkexec` should be used.


## Customization 
The button itself should be able to be customized with CSS although I didn't test it. Its class name is
`win-boot-button`.
