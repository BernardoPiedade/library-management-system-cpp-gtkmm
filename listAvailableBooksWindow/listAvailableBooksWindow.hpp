#include <gtkmm.h>
#include <string>

//Mysql headers
#include "../mysql_connection.h"
#include "../cppconn/driver.h"
#include "../cppconn/prepared_statement.h"

using namespace Gtk;

class listAvailableBooksWindow : public Window
{
	public:
		listAvailableBooksWindow();

	protected:
		//Tree model columns:
  		class ModelColumns : public Gtk::TreeModel::ColumnRecord
  		{
  			public:

    			ModelColumns()
    			{
    				add(tree_book_name);
    				add(tree_book_author);
    				add(tree_book_price);
    			}

    			Gtk::TreeModelColumn<std::string> tree_book_name;
    			Gtk::TreeModelColumn<std::string> tree_book_author;
    			Gtk::TreeModelColumn<int> tree_book_price;
		};

		ModelColumns m_Columns;

		//Child widgets:
		VBox m_VBox;

		Gtk::ScrolledWindow m_ScrolledWindow;
		Gtk::TreeView m_TreeView;
		Glib::RefPtr<Gtk::ListStore> m_refTreeModel;
};

listAvailableBooksWindow::listAvailableBooksWindow(){

	set_size_request(500, 200);
	set_position(WIN_POS_CENTER);
	set_resizable(false);
	set_border_width(10);
	set_title("List Available Books");


	m_VBox.set_homogeneous(true);
  	add(m_VBox);

  	//Add the TreeView, inside a ScrolledWindow

  	m_ScrolledWindow.add(m_TreeView);

  	m_VBox.add(m_ScrolledWindow);

  	m_refTreeModel = Gtk::ListStore::create(m_Columns);
  	m_TreeView.set_model(m_refTreeModel);

  	sql::Driver *driver;
  	sql::Connection *conn;

  	driver = get_driver_instance();
  	conn = driver->connect("localhost", "bernardo", "root");
  	conn->setSchema("library");

  	sql::PreparedStatement *pstmt;
  	pstmt = conn->prepareStatement("SELECT name, author, price FROM books WHERE available=1");

  	sql::ResultSet *result;
  	result = pstmt->executeQuery();

  	while(result->next()){
  		auto row = *(m_refTreeModel->append());
  		
  		row[m_Columns.tree_book_name] = result->getString(1).c_str();
  		row[m_Columns.tree_book_author] = result->getString(2).c_str();
  		row[m_Columns.tree_book_price] = result->getInt(3);
  	}

  	pstmt->close();
  	conn->close();

  	m_TreeView.append_column("Name", m_Columns.tree_book_name);
  	m_TreeView.append_column("Author", m_Columns.tree_book_author);
  	m_TreeView.append_column("Price", m_Columns.tree_book_price);

  	m_TreeView.get_column(0)->set_expand(true);
  	m_TreeView.get_column(1)->set_expand(true);
  	m_TreeView.get_column(2)->set_expand(true);

	show_all_children();
}
