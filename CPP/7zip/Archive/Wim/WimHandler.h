// WimHandler.h

#ifndef __ARCHIVE_WIM_HANDLER_H
#define __ARCHIVE_WIM_HANDLER_H

#include "../../../Common/MyCom.h"

#include "WimIn.h"

namespace NArchive {
namespace NWim {

class CHandler:
  public IInArchive,
  public IArchiveGetRawProps,
  public IArchiveGetRootProps,
  public IArchiveKeepModeForNextOpen,
  public ISetProperties,
  public IOutArchive,
  public CMyUnknownImp
{
  CDatabase _db;
  UInt32 _version;
  bool _isOldVersion;
  UInt32 _bootIndex;

  CObjectVector<CVolume> _volumes;
  CObjectVector<CWimXml> _xmls;
  // unsigned _nameLenForStreams;
  bool _xmlInComments;
  
  unsigned _numXmlItems;
  unsigned _numIgnoreItems;

  bool _xmlError;
  bool _isArc;

  bool _set_use_ShowImageNumber;
  bool _set_showImageNumber;
  int _defaultImageNumber;

  bool _showImageNumber;

  bool _keepMode_ShowImageNumber;

  UInt64 _phySize;
  int _firstVolumeIndex;

  void InitDefaults()
  {
    _set_use_ShowImageNumber = false;
    _set_showImageNumber = false;
    _defaultImageNumber = -1;
  }

  bool ThereIsError() const { return _xmlError || _db.ThereIsError(); }
  HRESULT GetSecurity(UInt32 realIndex, const void **data, UInt32 *dataSize, UInt32 *propType);

  HRESULT GetOutProperty(IArchiveUpdateCallback *callback, UInt32 callbackIndex, Int32 arcIndex, PROPID propID, PROPVARIANT *value);
  HRESULT        GetTime(IArchiveUpdateCallback *callback, UInt32 callbackIndex, Int32 arcIndex, PROPID propID, FILETIME &ft);
public:
  CHandler();
  MY_UNKNOWN_IMP6(
      IInArchive,
      IArchiveGetRawProps,
      IArchiveGetRootProps,
      IArchiveKeepModeForNextOpen,
      ISetProperties,
      IOutArchive)
  INTERFACE_IInArchive(;)
  INTERFACE_IArchiveGetRawProps(;)
  INTERFACE_IArchiveGetRootProps(;)
  STDMETHOD(SetProperties)(const wchar_t * const *names, const PROPVARIANT *values, UInt32 numProps);
  STDMETHOD(KeepModeForNextOpen)();
  INTERFACE_IOutArchive(;)
};

}}

#endif
