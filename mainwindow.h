#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <queue>
#include <stack>
#include <vector>
#include <functional>

// Struct to store information about a patient
struct Patient
{
    QString name;           // Patient's name
    int age;                // Patient's age
    QString condition;      // Medical condition of the patient
    int priority;           // Priority value for patient treatment (higher value = higher priority)
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor and Destructor
    MainWindow(QWidget *parent = nullptr);  // Constructor to initialize the UI and other components
    ~MainWindow();  // Destructor to clean up resources

private slots:
    // Slots that respond to user actions (like button clicks)
    void onAddPatientClicked();             // Slot for adding a new patient
    void onEmergencyRoomClicked();          // Slot for handling emergency room queue
    void onUndoClicked();                   // Slot for undoing actions (e.g., patient addition)
    void onTreatCriticalPatientClicked();   // Slot for treating the highest priority critical patient (NEW)

private:
    // UI components
    QTableWidget *patientTable;             // Table for displaying patient records
    QLineEdit *nameInput;                   // Input field for the patient's name
    QLineEdit *ageInput;                    // Input field for the patient's age
    QLineEdit *conditionInput;              // Input field for the patient's medical condition
    QSpinBox *priorityInput;                // Input field for the patient's treatment priority (NEW)
    QPushButton *addPatientButton;          // Button to add a new patient
    QPushButton *emergencyRoomButton;       // Button to manage emergency room operations
    QPushButton *undoButton;                // Button to undo the last action
    QPushButton *treatCriticalButton;       // Button to treat the highest priority critical patient (NEW)

    // Data structures for managing patients
    std::vector<Patient> patientRecords;    // Vector to store patient records (simulating a linked list)
    std::queue<Patient> emergencyQueue;     // Queue for managing emergency room patients (first-come, first-served)
    std::priority_queue<Patient, std::vector<Patient>, std::function<bool(Patient, Patient)>> criticalQueue;
    // Priority queue for handling critical patients (higher priority treated first)

    std::stack<Patient> treatmentStack;     // Stack to manage treatment order (Last-In, First-Out)

    // Function to update the patient table whenever there is a change in the records
    void updatePatientTable();
};

#endif // MAINWINDOW_H
