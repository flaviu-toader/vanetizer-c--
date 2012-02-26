#include <Wt/WApplication>
#include <Wt/WString>
#include <Wt/WText>
#include <Wt/WBorderLayout>
#include <Wt/WPanel>
#include <Wt/WStackedWidget>

#include "logger.h"
#include "client/navigationmenu.h"

class VanetizerApplication : public Wt::WApplication 
{
public:
    VanetizerApplication(const Wt::WEnvironment& environment, Wt::WtLibVersion version = Wt::WtWT_VERSION);
private:
    
};

VanetizerApplication::VanetizerApplication(const Wt::WEnvironment& environment, Wt::WtLibVersion version): WApplication(environment, version)
{
    Logger::entry("info", "Application successfully started!");
    messageResourceBundle().use("general");
    setTitle(Wt::WString::tr("application.title"));
    
    // define the main layout
    Wt::WBorderLayout *mainLayout = new Wt::WBorderLayout(root());
    
    // define here the title
    Wt::WPanel *titlePanel = new Wt::WPanel();
    titlePanel->setCentralWidget(new Wt::WText(Wt::WString::tr("application.title")));
    // add it to the main layout
    mainLayout->addWidget(titlePanel, Wt::WBorderLayout::North);
    
    Wt::WStackedWidget *contentsWidget = new Wt::WStackedWidget();
    mainLayout->addWidget(contentsWidget, Wt::WBorderLayout::Center);
    
    NavigationMenu *navigation = new NavigationMenu(contentsWidget);
    mainLayout->addWidget(navigation, Wt::WBorderLayout::West);

    setCssTheme("default");
    
    root()->setLayout(mainLayout);
}



Wt::WApplication *createApplication(const Wt::WEnvironment& env)
{
    return new VanetizerApplication(env);
}

int main(int argc, char **argv) 
{
    return Wt::WRun(argc, argv, &createApplication);
}
