# Qt Mini-GUI Editor (Canvas-Projekt)

Dieses Projekt ist im Rahmen des Moduls **Programmieren 2** an der Hochschule Darmstadt entstanden. Ziel war es, mithilfe von **C++ und Qt Widgets** eine kleine, selbstgemachte GUI-Designumgebung zu erstellen, in der Nutzer interaktiv Komponenten zeichnen, strukturieren und als Datei speichern oder laden können.

Als Ausgangspunkt diente ein vorgegebenes Code-Gerüst (siehe Ordner Gerüst), das lediglich die grafische Oberfläche enthielt – ohne funktionale Logik. Die vollständige Implementierung der Funktionalität (Zeichenlogik, Dateiverarbeitung, Eventhandling etc.) wurde eigenständig im Rahmen des Modulprojekt entwickelt.

Der Ordner Gerüst dokumentiert die unveränderte Originalbasis.
Das Hauptverzeichnis enthält das fertige, funktionstüchtige Projekt inklusive aller Erweiterungen und Strukturen.

---

## ✨ Features

- Interaktive GUI-Zeichenfläche (Canvas) mit Qt
- Unterstützte Komponenten: **Button**, **Container**
- **Drag-and-Drop-Zeichnung mit Gummiband-Effekt** von Komponenten per Maus (Start-/Endpunkt)
- **Design- & Event-Modus**: Buttons können angeklickt werden und lösen Events aus (Observer-Pattern)
- **Dateiformat-Unterstützung**:
  - Laden/Speichern in **XML**, **JSON**, **CSV**
  - Automatische Formatwahl anhand der Dateiendung
- **Farbauswahl** über GUI-Button („Set Color“) inkl. Speicherung
- Eingeschränkte Zeichenbedingungen (z. B. Mindestgröße, Container-Grenzen)

---

## 🛠️ Architektur & Technik

- **C++ mit Qt** (QWidget, QPainter, QMessageBox, QFileDialog, usw.)
- **Design Patterns**:
  - **Composite Pattern** zur hierarchischen Strukturierung von Komponenten
  - **Observer Pattern** zur Behandlung von Klick-Events auf Buttons
  - **Visitor Pattern** für Writer/Exporter (Dateiformat-Trennung)
- **Dreierregel beachtet** für Ressourcenverwaltung
- **Const-Correctness** und saubere Getter/Setter

---