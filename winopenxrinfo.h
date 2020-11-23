#ifndef WINOPENXRINFO_H
#define WINOPENXRINFO_H

#include <QHBoxLayout>
#include <QDialog>
#include <QLabel>
#include <QPushButton>

class WinOpenXRInfo : public QDialog
{
    Q_OBJECT

    QLabel* runtimeInfoDisplay = nullptr;
    QHBoxLayout* masterLayout = nullptr;
    QVBoxLayout* windowform = nullptr;
    QPushButton* quitButton = nullptr;
public:
    WinOpenXRInfo(QWidget *parent = nullptr);
    ~WinOpenXRInfo();
};
#endif // WINOPENXRINFO_H
