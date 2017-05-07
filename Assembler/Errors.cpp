#include "stdafx.h"
#include "Errors.h"

vector<string> Errors::m_ErrorMsgs;

void Errors::InitErrorReporting() {
	m_ErrorMsgs.erase(m_ErrorMsgs.begin(), m_ErrorMsgs.end());
}

void Errors::RecordError(string &a_emsg) {
	m_ErrorMsgs.push_back(a_emsg);
}

void Errors::DisplayErrors() {
	for (auto const& a: m_ErrorMsgs) {
		cout << a << endl;
	}
}

bool Errors::IsNoErrors() {
	return m_ErrorMsgs.empty();
}