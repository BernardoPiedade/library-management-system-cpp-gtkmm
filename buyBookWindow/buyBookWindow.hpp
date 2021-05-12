#include <gtkmm.h>
#include <string>

//Mysql headers
#include "../mysql_connection.h"
#include "../cppconn/driver.h"
#include "../cppconn/prepared_statement.h"

using namespace Gtk;

class buyBookWindow : public Window
{
	public:
		buyBookWindow();

		void populateTree();

		void event_clicked_buy_book();

	protected:
		//Tree model columns:
			class ModelColumns : public Gtk::TreeModel::ColumnRecord
			{
				public:

					ModelColumns()
					{
						add(tree_book_id);
						add(tree_book_name);
						add(tree_book_author);
						add(tree_book_price);
					}

					TreeModelColumn<unsigned int> tree_book_id;
					TreeModelColumn<std::string> tree_book_name;
					TreeModelColumn<std::string> tree_book_author;
					TreeModelColumn<int> tree_book_price;
		};

		ModelColumns m_Columns;

		//Child widgets:
		VBox m_VBox;

		ScrolledWindow m_ScrolledWindow;
		TreeView m_TreeView;
		Glib::RefPtr<Gtk::ListStore> m_refTreeModel;

		Box m_ButtonBox;
		Button m_Button_Buy;
};

buyBookWindow::buyBookWindow(){

	set_size_request(500, 350);
	set_position(WIN_POS_CENTER);
	set_resizable(false);
	set_border_width(10);
	set_title("Buy Book");


	m_VBox.set_homogeneous(false);
	add(m_VBox);

	//Add the TreeView, inside a ScrolledWindow

	m_ScrolledWindow.add(m_TreeView);

	m_VBox.add(m_ScrolledWindow);

	m_ButtonBox.add(m_Button_Buy);
	m_Button_Buy.set_label("Buy Book");
	m_Button_Buy.set_hexpand(true);
	m_Button_Buy.signal_clicked().connect(mem_fun(this, &buyBookWindow::event_clicked_buy_book));

	m_VBox.add(m_ButtonBox);

	populateTree();

	show_all_children();
}

void buyBookWindow::populateTree(){

	m_TreeView.remove_all_columns();

	m_refTreeModel = Gtk::ListStore::create(m_Columns);
	m_TreeView.set_model(m_refTreeModel);

	sql::Driver *driver;
	sql::Connection *conn;

	driver = get_driver_instance();
	conn = driver->connect("localhost", "bernardo", "root");
	conn->setSchema("library");

	sql::PreparedStatement *pstmt;
	pstmt = conn->prepareStatement("SELECT id, name, author, price FROM books WHERE available=1");

	sql::ResultSet *result;
	result = pstmt->executeQuery();

	while(result->next()){
		auto row = *(m_refTreeModel->append());
		
		row[m_Columns.tree_book_id] = result->getInt(1);
		row[m_Columns.tree_book_name] = result->getString(2).c_str();
		row[m_Columns.tree_book_author] = result->getString(3).c_str();
		row[m_Columns.tree_book_price] = result->getInt(4);
	}

	pstmt->close();
	conn->close();

	m_TreeView.append_column("id", m_Columns.tree_book_id);
	m_TreeView.append_column("Name", m_Columns.tree_book_name);
	m_TreeView.append_column("Author", m_Columns.tree_book_author);
	m_TreeView.append_column("Price", m_Columns.tree_book_price);

	m_TreeView.get_column(1)->set_expand(true);
	m_TreeView.get_column(2)->set_expand(true);
	m_TreeView.get_column(3)->set_expand(true);
}

void buyBookWindow::event_clicked_buy_book(){

	Glib::RefPtr<Gtk::TreeSelection> selection = m_TreeView.get_selection();
	TreeModel::iterator selectedRow = selection->get_selected();
	TreeModel::Row row = *selectedRow;
	unsigned int book_id = row.get_value(m_Columns.tree_book_id);

	sql::Driver *driver;
	sql::Connection *conn;

	driver = get_driver_instance();
	conn = driver->connect("localhost", "bernardo", "root");
	conn->setSchema("library");

	sql::PreparedStatement *pstmt;
    pstmt = conn->prepareStatement("UPDATE books SET available = ? WHERE id= ?");
    pstmt->setInt(1, 0);
    pstmt->setInt(2, book_id);
    pstmt->execute();
    pstmt->close();

    populateTree();

}
