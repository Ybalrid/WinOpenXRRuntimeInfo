#ifndef WINOPENXRINFO_H
#define WINOPENXRINFO_H

#include <QHBoxLayout>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>

class WinOpenXRInfo : public QDialog
{
    Q_OBJECT

    QLabel* runtimeInfoDisplay = nullptr;
    QLabel* runtimeManifestPath = nullptr;
    QLabel* runtimeLibaryPath = nullptr;

    QVBoxLayout* windowform = nullptr;
    QPushButton* quitButton = nullptr;
public:
    WinOpenXRInfo(QWidget *parent = nullptr);
    ~WinOpenXRInfo();
};
#endif // WINOPENXRINFO_H
