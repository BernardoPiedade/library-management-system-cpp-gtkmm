#include <gtkmm.h>
#include <string>

using namespace Gtk;

class errorWindow : public Window
{
	public:
		errorWindow();

	private:
		VBox vbox;

		Label label;
};

errorWindow::errorWindow(){
	set_size_request(500, 200);
	set_position(WIN_POS_CENTER);
	set_resizable(false);
	set_border_width(10);
	set_title("Error");

	label.set_label("Book price must be numeric");

	vbox.set_homogeneous(true);
	vbox.pack_start(label, true, true, 0);

	add(vbox);
	show_all_children();
}