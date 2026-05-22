<p align="center">
  <img src="web/assets/logo.png" alt="BRIDGE Logo" width="200"/>
</p>

<h1 align="center">🌉 BRIDGE</h1>
<p align="center"><b>Sign Language Translator</b></p>
<p align="center">
  Cross-platform desktop application with web interface
</p>

<p align="center">
  <img src="https://img.shields.io/badge/C++-17-blue?logo=c%2B%2B" alt="C++"/>
  <img src="https://img.shields.io/badge/Qt-6.5-green?logo=qt" alt="Qt"/>
  <img src="https://img.shields.io/badge/HTML5-orange?logo=html5" alt="HTML5"/>
  <img src="https://img.shields.io/badge/JavaScript-ES6+-yellow?logo=javascript" alt="JavaScript"/>
  <img src="https://img.shields.io/badge/License-MIT-green.svg" alt="License"/>
</p>

---

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Screenshots](#screenshots)
- [Architecture](#architecture)
- [Prerequisites](#prerequisites)
- [Building from Source](#building-from-source)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [API Documentation](#api-documentation)
- [Contributing](#contributing)
- [License](#license)

---

## Overview

BRIDGE is a cross-platform desktop application built with **C++ and Qt** that provides real-time sign language translation. It features a modern **HTML/CSS/JavaScript** web interface embedded via Qt WebEngine, combining native performance with web flexibility.

**Key Technologies:**
- **Backend:** C++17, Qt 6.5, OpenCV, ONNX Runtime
- **Frontend:** HTML5, CSS3, JavaScript (ES6+)
- **Communication:** Qt WebChannel (C++ ↔ JS bridge)

---

## Features

| Feature | Tech | Description |
|---------|------|-------------|
| 🎥 **Real-time Camera** | OpenCV + Qt Multimedia | Live webcam feed with hand detection |
| 🤟 **Sign Recognition** | ONNX Runtime | Local ML inference without cloud |
| 📝 **Text to Sign** | HTML Canvas | Animated sign language sequences |
| 🌐 **Web UI** | Qt WebEngine | Modern, responsive interface |
| ⚡ **Native Performance** | C++17 | 60 FPS video processing |
| 🔒 **Privacy-First** | Local Processing | No data leaves your device |

---

## Screenshots

### Main Interface
![Main Window](docs/screenshots/main_window.png)

### Real-time Translation
![Webcam Mode](docs/screenshots/webcam_mode.png)

### Text to Sign Animation
![Animation Mode](docs/screenshots/animation_mode.png)

### Settings Panel
![Settings](docs/screenshots/settings.png)

---

## Architecture

```
┌─────────────────────────────────────────┐
│           Qt Application (C++)            │
│  ┌─────────────────────────────────┐    │
│  │     Qt WebEngine (QWebView)      │    │
│  │  ┌───────────────────────────┐   │    │
│  │  │    HTML/CSS/JS UI        │   │    │
│  │  │  - Camera preview         │   │    │
│  │  │  - Animation canvas       │   │    │
│  │  │  - Results display        │   │    │
│  │  └───────────────────────────┘   │    │
│  └─────────────────────────────────┘    │
│              ↑↓ QWebChannel             │
│  ┌─────────────────────────────────┐    │
│  │      C++ Backend                │    │
│  │  - VideoCapture (OpenCV)        │    │
│  │  - HandDetector (MediaPipe)     │    │
│  │  - Predictor (ONNX Runtime)     │    │
│  │  - AnimationEngine              │    │
│  └─────────────────────────────────┘    │
└─────────────────────────────────────────┘
```

### Communication Flow

```javascript
// JavaScript → C++
bridge.predict(imageData).then(result => {
    console.log("Predicted:", result.sign);
});

// C++ → JavaScript
emit predictionReady(QString sign, double confidence);
```

---

## Prerequisites

### Required

| Dependency | Version | Purpose |
|------------|---------|---------|
| Qt | 6.5+ | GUI framework |
| CMake | 3.20+ | Build system |
| C++ Compiler | C++17 | GCC, Clang, or MSVC |
| OpenCV | 4.8+ | Computer vision |
| ONNX Runtime | 1.16+ | ML inference |

### Optional

| Dependency | Purpose |
|------------|---------|
| MediaPipe | Hand detection (alternative to OpenCV) |
| Qt WebEngine | Embedded browser |
| Node.js | Frontend build tools |

### Platform-Specific

**macOS (Apple Silicon):**
```bash
brew install qt@6 cmake opencv onnxruntime
```

**Ubuntu/Debian:**
```bash
sudo apt-get install qt6-base-dev qt6-webengine-dev cmake libopencv-dev
```

**Windows:**
- Install Qt via [Qt Online Installer](https://www.qt.io/download)
- Install OpenCV and ONNX Runtime via vcpkg

---

## Building from Source

### 1. Clone Repository

```bash
git clone https://github.com/YOUR_USERNAME/BRIDGE-CPP.git
cd BRIDGE-CPP
```

### 2. Configure Build

```bash
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH=/path/to/qt/6.5.0/macos
```

### 3. Build

```bash
cmake --build . --parallel $(nproc)
# or: make -j$(nproc)
# or: cmake --build . --config Release
```

### 4. Run

```bash
./BRIDGE
```

---

## Usage

### Launch Application

```bash
./BRIDGE
```

### Modes

| Mode | How to Access | Description |
|------|---------------|-------------|
| **Webcam** | Click camera icon | Real-time sign detection |
| **Text→Sign** | Click keyboard icon | Type text, see animation |
| **Upload** | Click upload icon | Predict from image file |
| **Settings** | Click gear icon | Adjust confidence threshold |

### Keyboard Shortcuts

| Key | Action |
|-----|--------|
| `Space` | Capture frame (webcam mode) |
| `Esc` | Exit current mode |
| `F11` | Toggle fullscreen |
| `Ctrl+Q` | Quit application |

---

## Project Structure

```
BRIDGE-CPP/
├── .gitignore
├── README.md
├── LICENSE
├── CMakeLists.txt
├── BRIDGE.pro              # Qt project file (alternative to CMake)
│
├── src/                     # C++ Source
│   ├── main.cpp
│   ├── mainwindow.cpp/h     # Main Qt window
│   ├── bridgecore.cpp/h     # Core application logic
│   ├── videocapture.cpp/h   # OpenCV camera handling
│   ├── predictor.cpp/h      # ONNX inference
│   ├── handdetector.cpp/h   # Hand detection
│   ├── animationengine.cpp/h # Sign animation
│   └── webbridge.cpp/h      # QWebChannel C++ side
│
├── include/                 # Public headers
│   └── bridge/
│       ├── api.h
│       └── types.h
│
├── web/                     # Frontend (HTML/CSS/JS)
│   ├── index.html
│   ├── css/
│   │   ├── main.css
│   │   ├── camera.css
│   │   └── animations.css
│   ├── js/
│   │   ├── app.js           # Main application
│   │   ├── camera.js        # Webcam handling
│   │   ├── bridge.js        # QWebChannel communication
│   │   ├── predictor.js     # Display predictions
│   │   └── animator.js      # Text→sign animation
│   └── assets/
│       ├── icons/
│       ├── fonts/
│       └── images/
│
├── models/                  # ML Models (download separately)
│   └── README.md
│
├── resources/               # Qt Resources
│   ├── qml/
│   ├── images/
│   └── translations/
│
├── tests/                   # Unit Tests
│   ├── test_predictor.cpp
│   └── test_animation.cpp
│
└── docs/                    # Documentation
    ├── screenshots/
    ├── api.md
    └── build.md
```

---

## API Documentation

### C++ Classes

#### `BridgeCore`
```cpp
class BridgeCore : public QObject {
    Q_OBJECT
public:
    explicit BridgeCore(QObject *parent = nullptr);

    // Camera control
    void startCamera();
    void stopCamera();

    // Prediction
    Q_INVOKABLE PredictionResult predict(const QImage &image);

    // Animation
    Q_INVOKABLE void playAnimation(const QString &text);

signals:
    void predictionReady(const QString &sign, double confidence);
    void animationFrameReady(const QImage &frame);
};
```

### JavaScript API

```javascript
// Initialize bridge
const bridge = new QWebChannel(qt.webChannelTransport, (channel) => {
    window.bridge = channel.objects.bridge;
});

// Predict from image
async function predictSign(imageData) {
    const result = await bridge.predict(imageData);
    return {
        sign: result.sign,
        confidence: result.confidence,
        top5: result.alternatives
    };
}

// Play text animation
bridge.playAnimation("HELLO WORLD");
```

---

## Frontend Technologies

### HTML Structure
```html
<!DOCTYPE html>
<html>
<head>
    <link rel="stylesheet" href="css/main.css">
    <script src="qrc:///qtwebchannel/qwebchannel.js"></script>
</head>
<body>
    <div id="app">
        <header><!-- Navigation --></header>
        <main id="camera-view"><!-- Camera feed --></main>
        <aside id="results"><!-- Predictions --></aside>
    </div>
    <script type="module" src="js/app.js"></script>
</body>
</html>
```

### CSS Features
- CSS Grid/Flexbox layouts
- CSS animations for sign transitions
- Dark/light theme support
- Responsive design

### JavaScript Features
- ES6+ modules
- Async/await for API calls
- Canvas API for animations
- WebRTC for camera access

---

## Building Frontend (Optional)

If you modify frontend files:

```bash
cd web
npm install        # If using build tools
npm run build      # Minify/bundle
# Or just edit files directly - Qt serves them as-is
```

---

## Contributing

### Setup Development Environment

```bash
# Clone with submodules
git clone --recursive https://github.com/YOUR_USERNAME/BRIDGE-CPP.git

# Install pre-commit hooks
pip install pre-commit
pre-commit install
```

### Coding Standards

- **C++:** Google C++ Style Guide, clang-format
- **JavaScript:** ESLint, Prettier
- **Git:** Conventional commits

### Submitting Changes

1. Fork the repository
2. Create feature branch: `git checkout -b feature/amazing-feature`
3. Commit changes: `git commit -m "feat: add amazing feature"`
4. Push to branch: `git push origin feature/amazing-feature`
5. Open Pull Request

---

## Troubleshooting

### Build Issues

| Problem | Solution |
|---------|----------|
| Qt not found | Set `CMAKE_PREFIX_PATH` to Qt installation |
| OpenCV linking error | Install `libopencv-dev` or set `OpenCV_DIR` |
| WebEngine not available | Install `qtwebengine` component |

### Runtime Issues

| Problem | Solution |
|---------|----------|
| Camera not detected | Check permissions (macOS: System Preferences → Security) |
| Model not loading | Download model from Releases, place in `models/` |
| Slow performance | Enable GPU acceleration in settings |

---

## Performance Benchmarks

| Platform | CPU | Inference Time | FPS |
|----------|-----|----------------|-----|
| macOS (M4) | Neural Engine | 2ms | 60 |
| macOS (M4) | CPU | 15ms | 30 |
| Windows (i7) | CPU | 25ms | 20 |
| Ubuntu (i9) | CPU | 20ms | 25 |

---

## Future Roadmap

- [ ] iOS/Android app using Qt for Mobile
- [ ] Cloud sync for learned signs
- [ ] Multi-language support (BSL, ISL, etc.)
- [ ] Voice synthesis output
- [ ] AR glasses integration

---

## Acknowledgments

- **Supervisor:** Eng. Mohamed Farag
- **ML Model:** Original BRIDGE Python project
- **Qt Framework:** The Qt Company
- **ONNX Runtime:** Microsoft

---

## License

MIT License - see [LICENSE](LICENSE) file.

---

## Contact

- **Author:** [Your Name]
- **Email:** [your.email@example.com]
- **Project Link:** [https://github.com/YOUR_USERNAME/BRIDGE-CPP](https://github.com/YOUR_USERNAME/BRIDGE-CPP)

---

<p align="center">
  <i>Building bridges, one sign at a time</i>
</p>
