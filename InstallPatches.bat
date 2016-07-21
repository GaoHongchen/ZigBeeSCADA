copy .\\MSCOMM\\MSCOMM.SRG %windir%\system32
copy .\\MSCOMM\\MSCOMM32.DEP %windir%\system32
copy .\\MSCOMM\\MSCOMM32.oca %windir%\system32
copy .\\MSCOMM\\mscomm32.ocx %windir%\system32

regsvr32 mscomm32.ocx
