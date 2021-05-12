#include <gtkmm.h>
#include <string>

using namespace Gtk;

class successWindow : public Window
{
	public:
		successWindow();

	private:
		VBox vbox;

		Label label;
};

successWindow::successWindow(){
	set_size_request(500, 200);
	set_position(WIN_POS_CENTER);
	set_resizable(false);
	set_border_width(10);
	set_title("Success");

	label.set_label("Book added successfully");

	vbox.set_homogeneous(true);
	vbox.pack_start(label, true, true, 0);

	add(vbox);
	show_all_children();
}