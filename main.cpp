#include <gtkmm.h>
#include "mainWindow.hpp"


using namespace Gtk;

int main(int argc, char *argv[]){
	Main main(argc, argv);
	MainWindow mainWindow;
	main.run(mainWindow);
}

MainWindow::MainWindow(){
	// create main window
	MainWindow::setWindow();

	// add main window buttons
	MainWindow::setButtons();

	show_all_children();
}