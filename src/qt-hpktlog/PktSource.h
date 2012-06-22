#ifndef	__PKTSOURCE_H__
#define	__PKTSOURCE_H__

#include <QtCore/QObject>
#include <QtCore/QTimerEvent>

#include <pcap.h>

#include "libradarpkt/pkt.h"

//
// This class provides a source of packet events.
//
// It's designed to be a base class for a packet source;
// this may include (say) a live pcap source, or a recorded
// pcap with timer events to "pace" how frequently the events
// come in.
//
// This class requires some destination to send each pcap entry
// to.
//
class PktSource : public QObject {

	Q_OBJECT

	private:
		pcap_t *PcapHdl;
		int timerId;

	public:
		PktSource() : PcapHdl(NULL), timerId(-1) { };
		~PktSource();
		bool Load(const char *filename);
		void Close();

	signals:
		void emitRadarEntry(struct radar_entry re);

	protected:
		void timerEvent(QTimerEvent *event);
};

#endif	/* __PKTSOURCE_H__ */
