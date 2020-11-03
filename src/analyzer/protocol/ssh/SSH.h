// See the file "COPYING" in the main distribution directory for copyright.

#pragma once

#include "zeek/analyzer/protocol/tcp/TCP.h"

#include "analyzer/protocol/ssh/events.bif.h"
#include "analyzer/protocol/ssh/ssh_pac.h"

namespace zeek::analyzer::ssh {

class SSH_Analyzer final : public analyzer::tcp::TCP_ApplicationAnalyzer {

public:
	explicit SSH_Analyzer(Connection* conn);
	~SSH_Analyzer() override;

	// Overriden from Analyzer.
	void Done() override;
	void DeliverStream(int len, const u_char* data, bool orig) override;
	void Undelivered(uint64_t seq, int len, bool orig) override;

	// Overriden from analyzer::tcp::TCP_ApplicationAnalyzer.
	void EndpointEOF(bool is_orig) override;

	static analyzer::Analyzer* Instantiate(Connection* conn)
		{ return new SSH_Analyzer(conn); }

protected:
	binpac::SSH::SSH_Conn* interp;

	void ProcessEncrypted(int len, bool orig);
	void ProcessEncryptedSegment(int len, bool orig);

	bool had_gap;

	// Packet analysis stuff
	bool auth_decision_made;
	bool skipped_banner;
	bool saw_encrypted_client_data;

	int service_accept_size;
	int userauth_failure_size;

};

} // namespace zeek::analyzer::ssh

namespace analyzer::SSH {

using SSH_Analyzer [[deprecated("Remove in v4.1. Use zeek::analyzer::ssh::SSH_Analyzer.")]] = zeek::analyzer::ssh::SSH_Analyzer;

} // namespace analyzer::SSH
