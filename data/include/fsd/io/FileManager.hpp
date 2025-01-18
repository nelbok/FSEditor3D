/*
 * Copyright (c) 2024 Foxxy Soft.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution
 */

#pragma once

#include <fsd/data/FSDataExport.h>

#include <QtCore/QDeadlineTimer>
#include <QtCore/QObject>
#include <QtCore/QUrl>

namespace fsd {
class Project;

/**
 * @brief Manager for loading or saving a project asynchronously.
 *
 * The manager uses JSON for the type file.\n
 * After initializing the manager and connecting finished() signal, call immediately start() function. \n
 * All functions can be called inside QML.
 */
class FSDATA_EXPORT FileManager : public QObject {
	Q_OBJECT

public:
	/**
	 * @brief Transaction type.
	 */
	enum class Type {
		/** To save the project */
		Save,
		/** To load the project */
		Load,
		/** Does nothing */
		NoType,
	};
	Q_ENUM(Type)

	/**
	 * @brief Transaction result.
	 */
	enum class Result {
		/** The transaction succeeded */
		Success,
		/** The transaction has been canceled */
		Canceled,
		/** An error occured during the transaction */
		Error,
		/** The transaction isn't started */
		NoResult,
	};
	Q_ENUM(Result)


	/**
	 *	@brief Default constructor.
	 */
	explicit FileManager(QObject* parent = nullptr);
	~FileManager() override = default;

	/**
	 * @brief Init the manager.
	 * @param[in]	project	Instance of the project
	 * @param[in]	type		Transaction type
	 * @param[in]	url			Url of the file on the disk
	 */
	Q_INVOKABLE void init(Project* project, Type type, const QUrl& url);
	/**
	 * @brief Begins execution of the thread by calling run(). See **QThread::start()**.
	 */
	Q_INVOKABLE void start();
	/**
	 * @brief Blocks the thread until conditions are met. See **QThread::wait()**.
	 */
	Q_INVOKABLE void wait(QDeadlineTimer deadline = QDeadlineTimer(QDeadlineTimer::Forever));
	/**
	 * @brief Returns true if the thread is finished; otherwise returns false. See **QThread::isFinished()**.
	 */
	Q_INVOKABLE bool isFinished() const;
	/**
	 * @brief Returns true if the thread is running; otherwise returns false. See **QThread::isRunning()**.
	 */
	Q_INVOKABLE bool isRunning() const;
	/**
	 * @brief Returns the result of the transaction after finished() signal has been emitted.
	 */
	Q_INVOKABLE Result result() const;
	/**
	 * @brief Returns the error message if the transaction failed.
	 */
	Q_INVOKABLE QString errorMessage() const;
	/**
	 * @brief Request the interruption of the thread. See **QThread::requestInterruption()**.
	 */
	Q_INVOKABLE void requestInterruption();

private:
	class Impl;
	Impl* _impl{ nullptr };

signals:
	/**
	 * @brief This signal is emitted from the associated thread right before it finishes executing. See **QThread::finished()**.
	 */
	void finished();
};
} // namespace fsd
