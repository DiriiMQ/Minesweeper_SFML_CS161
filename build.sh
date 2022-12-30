mkdir build_linux
cd build_linux
cmake ..
make 
cd ..
mkdir release_linux
mv build_linux/minesweeper_gui release_linux/minesweeper_gui

