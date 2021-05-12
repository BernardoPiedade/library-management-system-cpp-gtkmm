#include <gtkmm.h>

#include "listBooksWindow/listBooksWindow.hpp"
#include "listAvailableBooksWindow/listAvailableBooksWindow.hpp"
#include "buyBookWindow/buyBookWindow.hpp"
#include "addBookWindow/addBookWindow.hpp"

using namespace Gtk;
using namespace sigc;

class MainWindow : public Window
{
	public:
		MainWindow();

		void setWindow();
		void setButtons();

		void event_clicked_list_books_button();
		void event_clicked_list_available_books_button();
		void event_clicked_buy_book_button();
		void event_clicked_add_book_button();

	private:
		VBox vbox;

		// Buttons
		Button list_books_button;
		Button list_available_books_button;
		Button buy_book_button;
		Button add_book_button;

	protected:
		listBooksWindow* listBooksWindow_;
		listAvailableBooksWindow* listAvailableBooksWindow_;
		buyBookWindow* buyBookWindow_;
		addBookWindow* addBookWindow_;

};

void MainWindow::setWindow(){
	set_size_request(500, 200);
	set_position(WIN_POS_CENTER);
	set_resizable(false);
	set_border_width(10);
	set_title("Library Management System");
}

//add button
void MainWindow::setButtons(){
	
	// add list books button	
	list_books_button.set_label("List Books");
	list_books_button.set_size_request(100, 50);

	// add list available books button
	list_available_books_button.set_label("List Available Books");
	list_available_books_button.set_size_request(100, 50);

	// add buy book button
	buy_book_button.set_label("Buy Book");
	buy_book_button.set_size_request(100, 50);

	// add add book button
	add_book_button.set_label("Add Book");
	add_book_button.set_size_request(100, 50);

	// add buttons to window
	vbox.set_homogeneous(true);
	vbox.pack_start(list_books_button, true, true, 0);
	vbox.pack_start(list_available_books_button, true, true, 0);
	vbox.pack_start(buy_book_button, true, true, 0);
	vbox.pack_start(add_book_button, true, true, 0);


	// add events to buttons
	list_books_button.signal_clicked().connect(mem_fun(this, &MainWindow::event_clicked_list_books_button));
	list_available_books_button.signal_clicked().connect(mem_fun(this, &MainWindow::event_clicked_list_available_books_button));
	buy_book_button.signal_clicked().connect(mem_fun(this, &MainWindow::event_clicked_buy_book_button));
	add_book_button.signal_clicked().connect(mem_fun(this, &MainWindow::event_clicked_add_book_button));

	add(vbox);
}

void MainWindow::event_clicked_list_books_button(){
	listBooksWindow_ = new listBooksWindow;
	listBooksWindow_->show();
}

//TODO: create header files for new windows

void MainWindow::event_clicked_list_available_books_button(){
	listAvailableBooksWindow_ = new listAvailableBooksWindow;
	listAvailableBooksWindow_->show();
}

void MainWindow::event_clicked_buy_book_button(){
	buyBookWindow_ = new buyBookWindow;
	buyBookWindow_->show();
}

void MainWindow::event_clicked_add_book_button(){
	addBookWindow_ = new addBookWindow;
	addBookWindow_->show();
}