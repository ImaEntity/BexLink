# Executable Format Specification
**Note:** All multi-byte properties are in ***big endian***.

## File Header (24 bytes)

| Property      | Offset | Size | Function |
|---------------|--------|------|----------|
| `signature`   | 0      | 4    | The identifier used to recognize this executable type, `"BE\x04\xD5"`. |
| `version`     | 4      | 2    | The current format version of the executable, currently 1.2 (`0x01, 0x02`). |
| `flags`       | 6      | 1    | A list of flags describing file info (see table below). |
| `segmentCount`| 7      | 1    | Number of segments; must be at least 1 (to include `.code`). |
| `entryPoint`  | 8      | 8    | Address of the entry point, relative to `.code` start. |
| `baseAddress` | 16     | 8    | Expected base load address for pointer adjustment. |

### `flags` Bit Field (File Header)

| Bit | Meaning |
|-----|---------|
| 0   | If set, file is a linkable library. |
| 1   | If set, the file cannot be relocated. |
| 2–7 | Reserved for future use. |

---

## Segment Header (32 bytes)

| Property     | Offset | Size | Function |
|--------------|--------|------|----------|
| `name`       | 0      | 8    | Segment name, typically starts with a period. |
| `fileOffset` | 8      | 8    | Offset to segment data, from start of file. |
| `size`       | 16     | 8    | Size of segment data, in bytes. |
| `flags`      | 24     | 1    | Segment property flags (see below). |
| `reserved`   | 25     | 7    | Reserved for future use. |

### `flags` Bit Field (Segment Header)

| Bit | Meaning |
|-----|---------|
| 0   | If set, segment is executable. |
| 1   | If set, segment is writable. |
| 2–7 | Reserved for future use. |

---

## Relocation Table Entry (24 bytes)

| Property       | Offset | Size | Function |
|----------------|--------|------|----------|
| `offset`       | 0      | 8    | Offset relative to segment `segmentIdx` with address to patch. |
| `symNameOffset`| 8      | 8    | File offset to the symbol name (e.g., `lib32.bdl@methodName`). |
| `symNameLen`   | 16     | 2    | Length of the symbol name. |
| `segmentIdx`   | 17     | 1    | Index of the segment containing the address to patch. |
| `size`         | 18     | 1    | Number of bytes to patch. |
| `flags`        | 19     | 1    | Relocation flags (see below). |
| `reserved`     | 20     | 3    | Reserved for future use. |

### `flags` Bit Field (Relocation Entry)

| Bit | Meaning |
|-----|---------|
| 0   | If set, describes an absolute address. |
| 1   | If set, refers to an external file. |
| 2–7 | Reserved for future use. |

## Support
A header for C/C++ support is avalible here: [<u>bex.h</u>](https://github.com/ImaEntity/BexLink/blob/main/src/include/bex.h)
