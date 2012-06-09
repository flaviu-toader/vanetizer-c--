#ifndef CONFIGURATIONDIALOG_H
#define CONFIGURATIONDIALOG_H

#include <Wt/WDialog>

class MapPropertyEditor;
namespace Wt {
    class WTableView;
    class WPushButton;
}


class ConfigurationDialog : public Wt::WDialog
{
public:
    ConfigurationDialog(MapPropertyEditor* mapEditor);
    //! Get the selected configuration id.
    long long selectedConfig();
private:
    void submit(Wt::WDialog::DialogCode result);
    void removeClicked();
    void itemClicked(const Wt::WModelIndex& clickedItem);
    
    Wt::WTableView* configList_;
    Wt::WPushButton* removeButton_;
    Wt::WPushButton* okButton_;
    long long selectedConfig_;
    MapPropertyEditor* currentMpe_;
};

#endif // CONFIGURATIONDIALOG_H
