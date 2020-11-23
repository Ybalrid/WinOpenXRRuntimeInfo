#include "winopenxrinfo.h"
#define NOMINMAX
#include <Windows.h>
#include <QDebug>
#include <QFile>
#include <QJsonDocument>

WinOpenXRInfo::WinOpenXRInfo(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("OpenXR Active Runtime info");
    QLabel* titleLabel = new QLabel("Current OpenXR runtime:");
    //setMinimumSize(400, 200);

    windowform = new QVBoxLayout;
    auto masterLayout = new QHBoxLayout();
    masterLayout->addWidget(titleLabel);
    runtimeInfoDisplay = new QLabel("(not set)");
    masterLayout->addWidget(runtimeInfoDisplay);
    windowform->addLayout(masterLayout);

    masterLayout = new QHBoxLayout();
    titleLabel = new QLabel("Runtime manifest path:");
    masterLayout->addWidget(titleLabel);
    runtimeManifestPath = new QLabel("(not set)");
    masterLayout->addWidget(runtimeManifestPath);
    windowform->addLayout(masterLayout);

    masterLayout = new QHBoxLayout();
    titleLabel = new QLabel("Runtime library path:");
    masterLayout->addWidget(titleLabel);
    runtimeLibaryPath = new QLabel("(not set)");
    masterLayout->addWidget(runtimeLibaryPath);
    windowform->addLayout(masterLayout);

    quitButton = new QPushButton("Ok");
    windowform->addWidget(quitButton);
    QObject::connect(quitButton, &QPushButton::clicked, this, [&]{close();});

    setLayout(windowform);

    HKEY OpenXRKey = NULL;
    RegOpenKeyA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Khronos\\OpenXR\\1", &OpenXRKey);

    char path[MAX_PATH] = {0};
    DWORD size, type;
    LSTATUS readValueStatus = RegGetValueA(OpenXRKey, "", "ActiveRuntime", RRF_RT_REG_SZ, &type, (LPVOID)&path, &size);
    RegCloseKey(OpenXRKey);

    if(readValueStatus == ERROR_SUCCESS)
    {
        QFile file(path, this);
        file.open(QIODevice::ReadOnly);
        QByteArray content = file.readAll();
        auto currentRuntimeMannifest = QJsonDocument::fromJson(content);
        runtimeInfoDisplay->setText(currentRuntimeMannifest["runtime"]["name"].toString());
        runtimeManifestPath->setText(QString(path));
        runtimeLibaryPath->setText(currentRuntimeMannifest["runtime"]["library_path"].toString());
    }
    else
    {
        (void)QMessageBox::critical(this,
                                    "Registry Reading Error",
                                    "Cannot read ActiveRuntime from Registry.\n"
                                    "Please install an OpenXR Runtime.");
        this->close();
    }
}

WinOpenXRInfo::~WinOpenXRInfo()
{
}

