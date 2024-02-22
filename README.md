hisi (history Improved) is a command-line application that enhances the shell history navigation experience by providing Vim-like controls. Currently compatible only with zsh on macOS.

# Installation
1. Clone the repository
   ```shell
   git clone https://github.com/tergel93/hisi.git
   ```

2. Navigate to the cloned directory
   ```shell
   cd hisi
   ```
3. Build the application
   ```shell
   make
   ```
4. Install
   ```shell
   make install
   ```
   If installation fails, you may need to use sudo:
   ```shell
   sudo make install
   ```
5. To uninstall, use:
   ```shell
   make uninstall
   ```

## Usage
1. Type hisi in zsh.
2. Use 'j' or 'k' to navigate the cursor.
3. Press 'q' to exit (not like Vim).
4. Press 'y' to copy the current line to the clipboard then exit.
5. Press 'G' or 'gg' to go to the end or beginning of the history, respectively.
6. To move a long distance, press any number and then 'j' or 'k'.



