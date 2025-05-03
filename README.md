Certainly! Below is a detailed **README.md** file that includes instructions on how to compile the **Hospital Patient Record Management System** using Qt, as well as information on downloading precompiled versions from the releases for click-and-play usage.

---

# Hospital Patient Record Management System

## Overview

This **Hospital Patient Record Management System** allows hospitals or medical practitioners to manage patient records, treatment histories, emergency room queues, and critical patient prioritization. The system uses various data structures (arrays, linked lists, queues, stacks, and priority queues) for efficient real-time management of patient information and treatment records.

### Key Features:

* **Patient Record Management**: Add, edit, and delete patient records.
* **Emergency Room Queue**: FIFO (First In, First Out) queue for emergency patients.
* **Critical Patient Management**: Priority Queue for fast access to critical patients.
* **Treatment Undo Feature**: Stack-based undo feature for treatment history.
* **Real-Time Updates**: Use of Qt GUI for real-time interaction and updates.

---

## 📦 Prerequisites

Before building the system, ensure that you have the following installed:

### 1. **Qt Framework**:

The system is developed using **Qt 5.x or Qt 6.x**. To compile the project, you will need **Qt Creator** IDE.

* **Download Qt**: [Qt Downloads](https://www.qt.io/download)

  * Select the appropriate version based on your operating system (Windows, macOS, or Linux).
  * Follow the instructions to install **Qt Creator** and the Qt libraries.

### 2. **C++ Compiler**:

Ensure that you have a compatible C++ compiler installed. If you are using **Qt Creator**, it comes bundled with compatible compilers for all major platforms:

* **Windows**: MinGW or MSVC
* **macOS**: Clang (pre-installed with Xcode)
* **Linux**: GCC (most Linux distributions come with GCC pre-installed)

---

## 🛠️ Compiling the Project

### 1. **Download the Project**

You can either clone the repository or download the ZIP file from the releases page.

* **Download Precompiled Version**:
  Visit the [Releases](https://github.com/6vA7md9/HospitalManagementSystem/releases/) section and download the precompiled version for your operating system. The precompiled version is ready to use; simply extract the files and launch the application.

### 2. **Opening the Project in Qt Creator**

1. **Open Qt Creator**.
2. **Open the Project**: Click on `File -> Open File or Project` and select the `.pro` file located in the root directory of the downloaded project.
3. **Configure the Kit**: Qt Creator will prompt you to select a compiler and Qt version (e.g., Qt 5 or Qt 6). Select the correct kit based on your platform and preferences.

### 3. **Building the Project**

Once the project is loaded in **Qt Creator**, follow these steps to build the system:

* Click on the green **Build** button (the hammer icon) to compile the project.
* Qt Creator will automatically run `qmake` and compile the project.

### 4. **Running the Application**

After building the project, click on the **Run** button (the green play icon) to start the application. The GUI should open, and you can interact with the system.

---

## 🌟 Features and How to Use

### 1. **Patient Record Management**

* Add a new patient by clicking the `Add Patient` button.
* Edit or delete existing patient records by selecting the patient and clicking `Edit` or `Delete`.
* You can see a list of all patients in the left panel.

### 2. **Emergency Room Queue**

* The emergency room queue follows a **FIFO** model.
* Add emergency patients to the queue using the `Add to ER` button.

### 3. **Critical Patients**

* Critical patients are managed using a **Priority Queue**.
* Patients with higher priority will appear at the top of the list.
* You can add a patient to the critical queue by setting a high priority when adding a new patient.

### 4. **Treatment History & Undo**

* When a treatment is applied to a patient, it is recorded in the treatment history.
* To undo a treatment, click the `Undo Treatment` button.

---

## 📥 Downloading Precompiled Version

If you don't want to build the project from source, you can download a precompiled version directly from the **Releases** section.

1. Visit the [Releases](https://github.com/6vA7md9/HospitalManagementSystem/releases/) page.
2. Download the appropriate version for your operating system (Windows, macOS, or Linux).
3. Extract the downloaded archive to a folder.
4. Double-click the executable file to run the application.

---

## ⚙️ Troubleshooting

* **Missing Qt Libraries**:

  * Ensure that you have installed all necessary Qt dependencies. On some platforms, you might need to install the Qt runtime libraries separately.
  * You can find more information about this in the official Qt documentation: [Qt Installation Guide](https://doc.qt.io/qt-5.15/install.html).
* **Compiler Issues**:

  * If you encounter issues with the compiler, ensure that your C++ compiler (GCC, Clang, or MSVC) is installed and properly configured in **Qt Creator**.
* **GUI Issues**:

  * If the GUI doesn't load correctly, ensure that you're using a compatible version of Qt (5.x or 6.x).

---

## 🧑‍💻 Contributions

Feel free to contribute to this project by opening issues or submitting pull requests. Your contributions are welcome!
