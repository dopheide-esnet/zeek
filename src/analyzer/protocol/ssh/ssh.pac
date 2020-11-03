# Generated by binpac_quickstart

# Analyzer for Secure Shell
#  - ssh-protocol.pac: describes the SSH protocol messages
#  - ssh-analyzer.pac: describes the SSH analyzer code

%include binpac.pac
%include zeek.pac

%extern{
	#include "analyzer/protocol/ssh/types.bif.h"
	#include "analyzer/protocol/ssh/events.bif.h"
%}

analyzer SSH withcontext {
	connection: SSH_Conn;
	flow:       SSH_Flow;
};

# Our connection consists of two flows, one in each direction.
connection SSH_Conn(zeek_analyzer: ZeekAnalyzer) {
	upflow   = SSH_Flow(true);
	downflow = SSH_Flow(false);
};

%include ssh-protocol.pac

# Now we define the flow:
flow SSH_Flow(is_orig: bool) {
	flowunit = SSH_PDU(is_orig) withcontext(connection, this);
};

%include ssh-analyzer.pac