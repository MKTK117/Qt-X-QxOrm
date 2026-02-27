#ifndef QSINGLETON_H
#define QSINGLETON_H

#include <QMutex>
#include <QObject>
#include <QPointer>

template <typename T> class QSingleton {
public:
  static T *instance(QObject *parent = nullptr) {
    static QMutex mutex;
    QMutexLocker locker(&mutex);

    if (!_instance) {
      _instance = new T(parent);
    }
    return _instance;
  }

protected:
  QSingleton() = default;
  virtual ~QSingleton() = default;

  QSingleton(const QSingleton &) = delete;
  QSingleton &operator=(const QSingleton &) = delete;

private:
  static QPointer<T> _instance;
};

template <typename T> QPointer<T> QSingleton<T>::_instance = nullptr;

#endif // QSINGLETON_H