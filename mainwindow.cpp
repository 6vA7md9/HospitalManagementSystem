#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QFormLayout>

// Constructor: Initializes the main window, layout, and connections
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    criticalQueue([](const Patient &a, const Patient &b)
                  { return a.priority < b.priority; }) // Higher priority = comes first
{
    // Create the central widget and layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // Create the input fields for patient information
    nameInput = new QLineEdit(this);
    nameInput->setPlaceholderText("Enter Patient Name");
    ageInput = new QLineEdit(this);
    ageInput->setPlaceholderText("Enter Patient Age");
    conditionInput = new QLineEdit(this);
    conditionInput->setPlaceholderText("Enter Condition");

    // Create the priority input (spinbox)
    priorityInput = new QSpinBox(this);
    priorityInput->setRange(1, 10); // Set the range of priority from 1 to 10
    priorityInput->setValue(5); // Default priority is 5
    priorityInput->setPrefix("Priority: "); // Prefix to display with priority

    // Create buttons for adding patient, adding to emergency room, undoing, and treating critical patients
    addPatientButton = new QPushButton("Add Patient", this);
    emergencyRoomButton = new QPushButton("Add to Emergency Room", this);
    undoButton = new QPushButton("Undo Last Treatment", this);
    treatCriticalButton = new QPushButton("Treat Critical Patient", this); // NEW

    // Create the table to display patient records
    patientTable = new QTableWidget(this);
    patientTable->setColumnCount(3); // Three columns: Name, Age, Condition
    patientTable->setHorizontalHeaderLabels({"Name", "Age", "Condition"}); // Column headers
    patientTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // Auto resize columns

    // Add all widgets to the layout
    layout->addWidget(nameInput);
    layout->addWidget(ageInput);
    layout->addWidget(conditionInput);
    layout->addWidget(priorityInput);
    layout->addWidget(addPatientButton);
    layout->addWidget(emergencyRoomButton);
    layout->addWidget(undoButton);
    layout->addWidget(treatCriticalButton); // NEW
    layout->addWidget(patientTable);

    // Set the central widget of the main window
    setCentralWidget(centralWidget);

    // Connect the buttons to their respective slots (functions)
    connect(addPatientButton, &QPushButton::clicked, this, &MainWindow::onAddPatientClicked);
    connect(emergencyRoomButton, &QPushButton::clicked, this, &MainWindow::onEmergencyRoomClicked);
    connect(undoButton, &QPushButton::clicked, this, &MainWindow::onUndoClicked);
    connect(treatCriticalButton, &QPushButton::clicked, this, &MainWindow::onTreatCriticalPatientClicked); // NEW
}

// Destructor: Clean up resources
MainWindow::~MainWindow() {}

// Slot to handle adding a patient to the records
void MainWindow::onAddPatientClicked()
{
    QString name = nameInput->text();
    int age = ageInput->text().toInt(); // Convert the age input to integer
    QString condition = conditionInput->text();
    int priority = priorityInput->value(); // Get the priority level (spinbox value)

    // If any input is invalid, return without adding the patient
    if (name.isEmpty() || age <= 0 || condition.isEmpty())
        return;

    // Create a new patient object
    Patient newPatient = {name, age, condition, priority};

    // Push the new patient to the treatment stack
    treatmentStack.push(newPatient);

    // If the patient has a high priority (priority >= 8), add them to the critical queue
    if (priority >= 8)
    {
        criticalQueue.push(newPatient); // Add patient to critical queue
        QMessageBox::information(this, "Critical Patient", "Patient added to critical queue.");
    }
    else
    {
        patientRecords.push_back(newPatient); // Otherwise, add them to the regular records
        updatePatientTable(); // Update the table to reflect the new patient list
    }

    // Clear input fields after adding the patient
    nameInput->clear();
    ageInput->clear();
    conditionInput->clear();
    priorityInput->setValue(5); // Reset priority to default value
}

// Slot to handle adding a selected patient to the emergency room
void MainWindow::onEmergencyRoomClicked()
{
    if (patientRecords.empty()) {
        QMessageBox::warning(this, "Error", "No patients available to add to the emergency room.");
        return;
    }

    int selectedRow = patientTable->currentRow(); // Get the selected row from the table
    if (selectedRow < 0) {
        QMessageBox::warning(this, "Error", "Please select a patient to add to the emergency room.");
        return;
    }

    // Get the patient from the selected row
    Patient patient = patientRecords[selectedRow];

    // Push the patient to the emergency queue and remove from the regular records
    emergencyQueue.push(patient);
    patientRecords.erase(patientRecords.begin() + selectedRow);
    updatePatientTable(); // Update the patient table after removal

    QMessageBox::information(this, "Success", "Patient added to the emergency room.");
}

// Slot to handle undoing the last treatment (restores the last patient added)
void MainWindow::onUndoClicked()
{
    if (!treatmentStack.empty())
    {
        Patient lastPatient = treatmentStack.top(); // Get the last patient from the stack
        treatmentStack.pop(); // Remove the last patient from the stack
        patientRecords.push_back(lastPatient); // Add the patient back to the records
        updatePatientTable(); // Update the table
    }
}

// Slot to handle treating the most critical patient (highest priority)
void MainWindow::onTreatCriticalPatientClicked()
{
    if (criticalQueue.empty())
    {
        QMessageBox::information(this, "Info", "No critical patients to treat.");
        return;
    }

    // Get and remove the most critical patient (highest priority)
    Patient patient = criticalQueue.top();
    criticalQueue.pop();

    // Display a message indicating the treatment of the critical patient
    QMessageBox::information(this, "Treating Critical Patient",
                             QString("Treated: %1 (Priority %2)")
                                 .arg(patient.name)
                                 .arg(patient.priority));
}

// Updates the patient table to reflect the current list of patient records
void MainWindow::updatePatientTable()
{
    patientTable->setRowCount(patientRecords.size()); // Set the table row count based on the number of records
    for (size_t i = 0; i < patientRecords.size(); ++i)
    {
        patientTable->setItem(i, 0, new QTableWidgetItem(patientRecords[i].name)); // Name column
        patientTable->setItem(i, 1, new QTableWidgetItem(QString::number(patientRecords[i].age))); // Age column
        patientTable->setItem(i, 2, new QTableWidgetItem(patientRecords[i].condition)); // Condition column
    }
}
