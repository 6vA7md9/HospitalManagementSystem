#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QFormLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    criticalQueue([](const Patient &a, const Patient &b)
                  { return a.priority < b.priority; }) // Higher priority = comes first
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    nameInput = new QLineEdit(this);
    nameInput->setPlaceholderText("Enter Patient Name");
    ageInput = new QLineEdit(this);
    ageInput->setPlaceholderText("Enter Patient Age");
    conditionInput = new QLineEdit(this);
    conditionInput->setPlaceholderText("Enter Condition");

    priorityInput = new QSpinBox(this);
    priorityInput->setRange(1, 10);
    priorityInput->setValue(5);
    priorityInput->setPrefix("Priority: ");

    addPatientButton = new QPushButton("Add Patient", this);
    emergencyRoomButton = new QPushButton("Add to Emergency Room", this);
    undoButton = new QPushButton("Undo Last Treatment", this);
    treatCriticalButton = new QPushButton("Treat Critical Patient", this); // NEW

    patientTable = new QTableWidget(this);
    patientTable->setColumnCount(3);
    patientTable->setHorizontalHeaderLabels({"Name", "Age", "Condition"});
    patientTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    layout->addWidget(nameInput);
    layout->addWidget(ageInput);
    layout->addWidget(conditionInput);
    layout->addWidget(priorityInput);
    layout->addWidget(addPatientButton);
    layout->addWidget(emergencyRoomButton);
    layout->addWidget(undoButton);
    layout->addWidget(treatCriticalButton); // NEW
    layout->addWidget(patientTable);

    setCentralWidget(centralWidget);

    connect(addPatientButton, &QPushButton::clicked, this, &MainWindow::onAddPatientClicked);
    connect(emergencyRoomButton, &QPushButton::clicked, this, &MainWindow::onEmergencyRoomClicked);
    connect(undoButton, &QPushButton::clicked, this, &MainWindow::onUndoClicked);
    connect(treatCriticalButton, &QPushButton::clicked, this, &MainWindow::onTreatCriticalPatientClicked); // NEW
}

MainWindow::~MainWindow() {}

void MainWindow::onAddPatientClicked()
{
    QString name = nameInput->text();
    int age = ageInput->text().toInt();
    QString condition = conditionInput->text();
    int priority = priorityInput->value(); // NEW

    if (name.isEmpty() || age <= 0 || condition.isEmpty())
        return;

    Patient newPatient = {name, age, condition, priority};
    treatmentStack.push(newPatient);

    if (priority >= 8)
    {
        criticalQueue.push(newPatient);
        QMessageBox::information(this, "Critical Patient", "Patient added to critical queue.");
    }
    else
    {
        patientRecords.push_back(newPatient);
        updatePatientTable();
    }

    nameInput->clear();
    ageInput->clear();
    conditionInput->clear();
    priorityInput->setValue(5);
}

void MainWindow::onEmergencyRoomClicked()
{
    if (patientRecords.empty()) {
        QMessageBox::warning(this, "Error", "No patients available to add to the emergency room.");
        return;
    }

    int selectedRow = patientTable->currentRow();
    if (selectedRow < 0) {
        QMessageBox::warning(this, "Error", "Please select a patient to add to the emergency room.");
        return;
    }

    Patient patient = patientRecords[selectedRow];
    emergencyQueue.push(patient);
    patientRecords.erase(patientRecords.begin() + selectedRow);
    updatePatientTable();

    QMessageBox::information(this, "Success", "Patient added to the emergency room.");
}

void MainWindow::onUndoClicked()
{
    if (!treatmentStack.empty())
    {
        Patient lastPatient = treatmentStack.top();
        treatmentStack.pop();
        patientRecords.push_back(lastPatient);
        updatePatientTable();
    }
}

void MainWindow::onTreatCriticalPatientClicked()
{
    if (criticalQueue.empty())
    {
        QMessageBox::information(this, "Info", "No critical patients to treat.");
        return;
    }

    Patient patient = criticalQueue.top();
    criticalQueue.pop();

    QMessageBox::information(this, "Treating Critical Patient",
                             QString("Treated: %1 (Priority %2)")
                                 .arg(patient.name)
                                 .arg(patient.priority));
}

void MainWindow::updatePatientTable()
{
    patientTable->setRowCount(patientRecords.size());
    for (size_t i = 0; i < patientRecords.size(); ++i)
    {
        patientTable->setItem(i, 0, new QTableWidgetItem(patientRecords[i].name));
        patientTable->setItem(i, 1, new QTableWidgetItem(QString::number(patientRecords[i].age)));
        patientTable->setItem(i, 2, new QTableWidgetItem(patientRecords[i].condition));
    }
}
