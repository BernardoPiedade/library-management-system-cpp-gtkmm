#include <gtkmm.h>
#include <string>

#include "errorWindow/errorWindow.hpp"
#include "successWindow/successWindow.hpp"

//Mysql headers
#include "../mysql_connection.h"
#include "../cppconn/driver.h"
#include "../cppconn/prepared_statement.h"

using namespace Gtk;
using namespace sigc;

class addBookWindow : public Window
{
	public:
		addBookWindow();

		void event_clicked_add_book();
		bool check_number(std::string str);

	private:
		Grid grid;

		// Buttons
		Button add_book_button; // grid line 4

		// Labels
		Label book_name_label; // grid line 1
		Label book_author_label; // grid line 2
		Label book_price_label; // grid line 3

		// Inputs
		Entry book_name_entry; // grid line 1
		Entry book_author_entry; // grid line 2
		Entry book_price_entry; //grid line 3

	protected:
		errorWindow* errorWindow_;
		successWindow* successWindow_;


};

addBookWindow::addBookWindow(){
	set_size_request(500, 200);
	set_position(WIN_POS_CENTER);
	set_resizable(false);
	set_border_width(10);
	set_title("Add Book");

	// add button label and function
	add_book_button.set_label("Add Book");
	add_book_button.signal_clicked().connect(mem_fun(this, &addBookWindow::event_clicked_add_book));

	// add book name label text
	book_name_label.set_label("Book Name: ");
	
	// add book author label text
	book_author_label.set_label("Book Author: ");

	// add book price label text
	book_price_label.set_label("Book Price: ");
	

	// grid config
	grid.set_row_homogeneous(true);
	grid.set_column_homogeneous(true);
	grid.set_row_spacing(2);
	grid.set_column_spacing(2);

	// add to grid
	// book name
	grid.attach(book_name_label, 0, 0, 1, 1);
	grid.attach(book_name_entry, 1, 0, 1, 1);

	// book author
	grid.attach(book_author_label, 0, 1, 1, 1);
	grid.attach(book_author_entry, 1, 1, 1, 1);

	//book price
	grid.attach(book_price_label, 0, 2, 1, 1);
	grid.attach(book_price_entry, 1, 2, 1, 1);

	// button
	grid.attach(add_book_button, 0, 3, 2, 2);
	
	add(grid);

	show_all_children();
}

void addBookWindow::event_clicked_add_book(){
	std::string b_name = book_name_entry.get_text();
	std::string b_author = book_author_entry.get_text();
	std::string b_price = book_price_entry.get_text();

	if(addBookWindow::check_number(b_price)){

		sql::Driver *driver;
		sql::Connection *conn;

		driver = get_driver_instance();
		conn = driver->connect("localhost", "bernardo", "root");
		conn->setSchema("library");

		sql::PreparedStatement *pstmt;
	    pstmt = conn->prepareStatement("INSERT INTO books (name, author, price, available) VALUES (?, ?, ?, 1)");
	    pstmt->setString(1, b_name);
	    pstmt->setString(2, b_author);
	    pstmt->setInt(3, stoi(b_price));
	    pstmt->execute();
	    pstmt->close();

	    book_name_entry.set_text("");
	    book_author_entry.set_text("");
	    book_price_entry.set_text("");

	    successWindow_ = new successWindow;
	    successWindow_->show();
	}else{
		errorWindow_ = new errorWindow;
		errorWindow_->show();
	}
}

bool addBookWindow::check_number(std::string str) {
   	for (size_t i = 0; i < str.length(); i++)
   		if (isdigit(str[i]) == false)
      		return false;
    return true;
}
