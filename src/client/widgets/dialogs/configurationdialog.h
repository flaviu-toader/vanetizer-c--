#ifndef CONFIGURATIONDIALOG_H
#define CONFIGURATIONDIALOG_H

#include <Wt/WDialog>

namespace Wt {
    class WTableView;
    class WPushButton;
}


class ConfigurationDialog : public Wt::WDialog
{
public:
    ConfigurationDialog();
private:
    void submit(Wt::WDialog::DialogCode result);
    void removeClicked();
    void itemClicked();
    
    Wt::WTableView* configList_;
    Wt::WPushButton* removeConfig_;
    Wt::WPushButton* okButton_;
    long long selectedConfig_;
};

#endif // CONFIGURATIONDIALOG_H
