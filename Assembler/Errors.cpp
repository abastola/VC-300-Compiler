#include "stdafx.h"
#include "Errors.h"

vector<string> Errors::m_ErrorMsgs;

/**/
/*
void Errors::InitErrorReporting()
NAME
	Errors::InitErrorReporting()
SYNOPSIS
	void Errors::InitErrorReporting()
DESCRIPTION
	Intializes Error Reporting
RETURNS
	VOID
AUTHOR
	Arjun Bastola
DATE
	3:08 PM 5/7/2017
*/
/**/

void Errors::InitErrorReporting() {
	m_ErrorMsgs.erase(m_ErrorMsgs.begin(), m_ErrorMsgs.end());
}

/**/
/*
void Errors::RecordError(string &a_emsg)
NAME
	Errors::RecordError(string &a_emsg)
SYNOPSIS
	void Errors::RecordError(string &a_emsg)
	a_emsg --> Error Message to be recorded
DESCRIPTION
	Adds Error message to the Errors List
RETURNS
	VOID
AUTHOR
	Arjun Bastola
DATE
	3:08 PM 5/7/2017
*/
/**/


void Errors::RecordError(string &a_emsg) {
	m_ErrorMsgs.push_back(a_emsg);
}

/**/
/*
void Errors::DisplayErrors()
NAME
	Errors::DisplayErrors()
SYNOPSIS
	void Errors::DisplayErrors()
DESCRIPTION
	Displays Errors from m_ErrorMsgs
RETURNS
	VOID
AUTHOR
	Arjun Bastola
DATE
	3:08 PM 5/7/2017
*/
/**/

void Errors::DisplayErrors() {
	for (auto const& a: m_ErrorMsgs) {
		cout << a << endl;
	}
}

/**/
/*
bool Errors::IsNoErrors()
NAME
	Errors::IsNoErrors()
SYNOPSIS
	bool Errors::IsNoErrors()
DESCRIPTION
	Returns true if no errors
RETURNS
	Returns true if no errors, false if errors
AUTHOR
	Arjun Bastola
DATE
	3:08 PM 5/7/2017
*/
/**/

bool Errors::IsNoErrors() {
	return m_ErrorMsgs.empty();
}