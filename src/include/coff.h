#ifndef HH_COFF
#define HH_COFF

#include "types.h"

typedef struct {
	word f_magic;  /* Magic number */	
	word f_nscns;  /* Number of Sections */
	int f_timdat;  /* Time & date stamp */
	int f_symptr;  /* File pointer to Symbol Table */
	int f_nsyms;   /* Number of Symbols */
	word f_opthdr; /* sizeof(Optional Header) */
	word f_flags;  /* Flags */
} COFFHeader;

typedef struct {
	 word magic;      /* Magic Number                    */
	 word vstamp;     /* Version stamp                   */
	dword tsize;      /* Text size in bytes              */
	dword dsize;      /* Initialised data size           */
	dword bsize;      /* Uninitialised data size         */
	dword entry;      /* Entry point                     */
	dword text_start; /* Base of Text used for this file */
	dword data_start; /* Base of Data used for this file */
} COFFOptionalHeader;

#endif