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

    SimulationOutput so_;
};

#endif // RUNRESULTDIALOG_H
