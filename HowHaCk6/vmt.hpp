#pragma once
#ifndef VMT_H
#define VMT_H

#include <Windows.h>
#include <malloc.h>

class VMTHook
{
public:
	void** m_pOriginalVTable;
	void** m_pNewVTable;
	void*** m_pInstance;

	int m_iNumIndices;
	//funcs

	VMTHook(void* instance);
	~VMTHook();

	int tellCount();

	void* hookFunction(int iIndex, void* pfnHook);
	void* unhookFunction(int iIndex);
	void* GetMethod(int iIndex);
	void* GetHookedMethod(int iIndex);
	void SetPadding(int pad);

	int padding;

};


VMTHook::VMTHook(void* instance)
{
	padding = 0;

	if (!instance)
		return;

	m_pInstance = (void***)instance;

	if (!m_pInstance)
		return;

	m_pOriginalVTable = *m_pInstance;

	if (!m_pOriginalVTable)
		return;

	//Count number of Pointers in the table


	m_iNumIndices = 0;

	while (m_pOriginalVTable[m_iNumIndices])
	{
		m_iNumIndices++;
	}

	if (!m_iNumIndices)
		return;

	//Allocate memory on the heap for our own copy of the table
	int size = sizeof(int) * (m_iNumIndices + 6);

	m_pNewVTable = (void**)malloc(size);

	if (!m_pNewVTable)
		return;


	int i = -2;

	while (++i < m_iNumIndices)
	{
		m_pNewVTable[i] = m_pOriginalVTable[i];

	}


	*m_pInstance = m_pNewVTable;
	FlushInstructionCache(GetCurrentProcess(), 0, 0);

}

VMTHook::~VMTHook()
{

	//Rewrite old pointer

	if (!m_pInstance)
		return;

	if (!*m_pInstance)
		return;

	if (!m_pOriginalVTable)
		return;

	if (m_pNewVTable)
	{
		for (int i = 0; i < m_iNumIndices; i++)
		{
			if (m_pNewVTable[i] != m_pOriginalVTable[i])
			{
				m_pNewVTable[i] = m_pOriginalVTable[i];
			}
		}
		//free(m_pNewVTable);
	}


	*m_pInstance = m_pOriginalVTable;
	FlushInstructionCache(GetCurrentProcess(), 0, 0);

	return;

}

int VMTHook::tellCount()
{

	return m_iNumIndices;
}

void* VMTHook::hookFunction(int iIndex, void* pfnHook)
{
	if (padding)
		iIndex = iIndex + padding;

	//Valid index?
	if (iIndex >= m_iNumIndices)
		return NULL;

	if (!m_pOriginalVTable[iIndex])
		return NULL;

	if (pfnHook == m_pOriginalVTable[iIndex])
		return 0;

	//Write new pointer
	m_pNewVTable[iIndex] = pfnHook;

	FlushInstructionCache(GetCurrentProcess(), 0, 0);

	//And return pointer to original function
	return m_pOriginalVTable[iIndex];
}

void* VMTHook::unhookFunction(int iIndex)
{
	if (padding)
		iIndex = iIndex + padding;

	//Valid index?
	if (iIndex >= m_iNumIndices)
		return NULL;

	if (!m_pOriginalVTable[iIndex])
		return NULL;

	//Rewrite old pointer
	m_pNewVTable[iIndex] = m_pOriginalVTable[iIndex];

	FlushInstructionCache(GetCurrentProcess(), 0, 0);

	//And return pointer to original function
	return m_pOriginalVTable[iIndex];
}
void* VMTHook::GetMethod(int iIndex)
{
	if (padding)
		iIndex = iIndex + padding;

	return m_pOriginalVTable[iIndex];
}
void* VMTHook::GetHookedMethod(int iIndex)
{
	if (padding)
		iIndex = iIndex + padding;

	return m_pNewVTable[iIndex];
}

void VMTHook::SetPadding(int pad)
{
	padding = pad;
}


// This is from Gaztoof

template<typename T>
T* GetVMT(uintptr_t address, int index, uintptr_t offset) // Address must be a VTable pointer, not a VTable !
{
#ifdef _WIN64
	uintptr_t step = 3;
	uintptr_t instructionSize = 7;
	uintptr_t instruction = ((*(uintptr_t**)(address))[index] + offset);

	uintptr_t relativeAddress = *(DWORD*)(instruction + step);
	uintptr_t realAddress = instruction + instructionSize + relativeAddress;
	return *(T**)(realAddress);
#else
	uintptr_t instruction = ((*(uintptr_t**)(address))[index] + offset);
	return *(T**)(*(uintptr_t*)(instruction));
#endif
}
template<typename T>
T* GetVMT(uintptr_t address, uintptr_t offset) // This doesn't reads from the VMT, address must be the function's base ! Not a pointer!
{
#ifdef _WIN64
	uintptr_t step = 3;
	uintptr_t instructionSize = 7;
	uintptr_t instruction = address + offset;

	uintptr_t relativeAddress = *(DWORD*)(instruction + step);
	uintptr_t realAddress = instruction + instructionSize + relativeAddress;
	return *(T**)(realAddress);
#else
	uintptr_t instruction = (address + offset);
	return *(T**)(*(uintptr_t*)(instruction));
#endif
}

#endif