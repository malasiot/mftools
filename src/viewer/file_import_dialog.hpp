#ifndef __FILE_IMPORT_DIALOG_H__
#define __FILE_IMPORT_DIALOG_H__

#include <QDialog>
#include <QThread>
#include <QAtomicInt>

#include "data_import.hpp"

class QPushButton ;
class QProgressBar ;
class QLabel ;
class MapFeatureIndex ;
class MapFeatureCollection ;
class FileImportWorker ;

class FileImportDialog: public QDialog
{
    Q_OBJECT

public:
    FileImportDialog(const QStringList &files, quint64 parent_folder_id, MapFeatureIndex *index, QWidget *parent);

    QVector<CollectionData *> collections_ ;
    QVector<CollectionTreeNode *> documents_ ;

public Q_SLOTS:

    void stop() ;
    void finished() ;
    void setMessage(const QString &txt);
    void setProgress(int) ;
    void start();
private:

    QPushButton *stop_button_ ;
    QLabel *name_label_;
    QProgressBar *progress_bar_;


    FileImportWorker *worker_ ;
};


class FileImportWorker: public QThread
{
public:
    FileImportWorker(const QStringList &files, quint64 folder_id, MapFeatureIndex *feature_index):
        stop_flag_(0), files_(files), parent_folder_id_(folder_id), index_(feature_index) {}

private:
    Q_OBJECT

    friend class FileImportDialog ;

    QVector<CollectionData *> collections_ ;
    QVector<CollectionTreeNode *> documents_ ;

    void stop() {
        stop_flag_ = 1 ;
    }

    QAtomicInt stop_flag_ ;
    QStringList files_ ;
    quint64 parent_folder_id_ ;
    MapFeatureIndex *index_ ;

 public:

     void run() ;

 Q_SIGNALS:

     void importStarted(const QString &fileName);
     void importFinished(int) ;
 };

#endif
