#ifndef RUNRESULTDIALOG_H
#define RUNRESULTDIALOG_H

#include <Wt/WDialog>

class SimulationOutput;

class RunResultDialog : public Wt::WDialog
{
public:
    RunResultDialog(const SimulationOutput& so);
private:
    void nodesInputClicked();
    void mobilityInClicked();
    void glomoStatClicked();
    void closeDialog();
    void removeFile(const std::string& filename);
    void downloadFile(const std::string& newFileName);

    SimulationOutput so_;
};

#endif // RUNRESULTDIALOG_H
