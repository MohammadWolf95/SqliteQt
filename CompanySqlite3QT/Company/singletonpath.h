#ifndef SINGLETONPATH_H
#define SINGLETONPATH_H
#include <QWidget>

class Singletonpath;  // опережающее объявление

class SingletonpathDestroyer
{
  private:
    Singletonpath* p_instance;
  public:
    ~SingletonpathDestroyer();
    void initialize( Singletonpath* p );
};

class Singletonpath
{
  private:
    static Singletonpath* p_instance;
    static SingletonpathDestroyer destroyer;
  protected:
    Singletonpath() { }
    Singletonpath( const Singletonpath& );
    Singletonpath& operator=( Singletonpath& );
   ~Singletonpath() { }
    friend class SingletonpathDestroyer;
  public:
    static Singletonpath& getInstance();
    QString sqlpath;
};

#endif // SINGLETONPATH_H
