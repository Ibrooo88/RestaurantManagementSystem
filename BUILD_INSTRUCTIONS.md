# تعليمات البناء والتشغيل

## المتطلبات الأساسية

### Windows:
1. **CMake** - تحميل من [cmake.org](https://cmake.org/download/)
2. **Qt5** - تحميل من [qt.io](https://www.qt.io/download)
3. **Visual Studio** أو **MinGW** (للتجميع)
4. **SQLite3** - عادةً يأتي مع Qt

### Linux (Ubuntu/Debian):
```bash
sudo apt-get update
sudo apt-get install cmake qt5-default qtbase5-dev libsqlite3-dev build-essential
```

### macOS:
```bash
brew install cmake qt5 sqlite3
```

## خطوات البناء

### 1. إنشاء مجلد البناء
```bash
mkdir build
cd build
```

### 2. تشغيل CMake
```bash
cmake ..
```

### 3. التجميع
```bash
# Windows (Visual Studio)
cmake --build . --config Release

# Linux/macOS
make
```

### 4. التشغيل
```bash
# Windows
.\bin\RestaurantManagementSystem.exe

# Linux/macOS
./bin/RestaurantManagementSystem
```

## ملاحظات مهمة

1. **قاعدة البيانات**: سيتم إنشاء ملف `restaurant.db` تلقائياً عند أول تشغيل
2. **الملفات المطلوبة**: تأكد من وجود جميع ملفات المصدر في المجلدات الصحيحة
3. **Qt MOC**: CMakeLists.txt يتعامل تلقائياً مع ملفات MOC للـ Qt

## حل المشاكل الشائعة

### خطأ: "Could not find Qt5"
- تأكد من تثبيت Qt5
- أضف مسار Qt إلى PATH
- أو حدد مسار Qt في CMake:
  ```bash
  cmake -DCMAKE_PREFIX_PATH=/path/to/qt5 ..
  ```

### خطأ: "Could not find SQLite3"
- على Windows: تأكد من وجود SQLite3 في PATH
- على Linux: `sudo apt-get install libsqlite3-dev`
- على macOS: `brew install sqlite3`

### خطأ في التجميع
- تأكد من استخدام C++17 أو أحدث
- تحقق من جميع الـ includes
- راجع ملفات السجل (logs)

## التطوير

لإضافة ملفات جديدة:
1. أضف الملف إلى `CMakeLists.txt` في قسم `SOURCES` أو `HEADERS`
2. أعد تشغيل CMake
3. أعد التجميع

