/******************************************************************************
 * QSkinny - Copyright (C) 2016 Uwe Rathmann
 * This file may be used under the terms of the QSkinny License, Version 1.0
 *****************************************************************************/

#ifndef QSK_INPUT_COMPOSITION_MODEL_H
#define QSK_INPUT_COMPOSITION_MODEL_H

#include <QObject>

#include <memory>

class QInputMethodEvent;
class QskInputContext;

class QskInputCompositionModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY( QVector< Qt::Key > groups READ groups NOTIFY groupsChanged )

public:
    QskInputCompositionModel( QskInputContext* context );
    virtual ~QskInputCompositionModel();

    // to determine whether to show the suggestion bar:
    virtual bool supportsSuggestions() const;

    void commit( const QString& );
    virtual void commitCandidate( int );
    void composeKey( Qt::Key );

    void clearPreedit();

    virtual int candidateCount() const;
    virtual QString candidate( int ) const;

    int groupIndex() const;
    void setGroupIndex( int groupIndex );
    virtual bool nextGroupIndex( int&, bool = true ) const;

    virtual QVector< Qt::Key > groups() const;

protected:
    // Used for text composition
    virtual bool hasIntermediate() const;
    virtual QString polishPreedit( const QString& preedit );
    virtual bool isComposable( const QStringRef& preedit ) const;

    QskInputContext* context() const;

Q_SIGNALS:
    void groupsChanged( const QVector< Qt::Key >& );
    void candidatesChanged();

private:
    void sendCompositionEvent( QInputMethodEvent* e );
    void sendKeyEvents( int key );

    class PrivateData;
    std::unique_ptr< PrivateData > m_data;
};

#endif
