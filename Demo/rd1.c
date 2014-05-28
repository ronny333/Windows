#include <ntddk.h>
#include<wdm.h>
#ifndef __EXAMPLE_H__
#define __EXAMPLE_H__

typedef unsigned int UINT;
typedef char *PCHAR;

/* #define __USE_DIRECT__ */
/* #define __USE_BUFFERED__ */

NTSTATUS Example_Create(PDEVICE_OBJECT DeviceObject, PIRP Irp);
NTSTATUS Example_Close(PDEVICE_OBJECT DeviceObject, PIRP Irp);
NTSTATUS Example_IoControl(PDEVICE_OBJECT DeviceObject, PIRP Irp);
NTSTATUS Example_Read(PDEVICE_OBJECT DeviceObject, PIRP Irp);
NTSTATUS Example_WriteBufferedIO(PDEVICE_OBJECT DeviceObject, PIRP Irp);
NTSTATUS Example_WriteDirectIO(PDEVICE_OBJECT DeviceObject, PIRP Irp);
NTSTATUS Example_WriteNeither(PDEVICE_OBJECT DeviceObject, PIRP Irp);
NTSTATUS Example_UnSupportedFunction(PDEVICE_OBJECT DeviceObject, PIRP Irp);

#ifdef __USE_DIRECT__
#define IO_TYPE DO_DIRECT_IO
#define USE_WRITE_FUNCTION  Example_WriteDirectIO
#endif
 
#ifdef __USE_BUFFERED__
#define IO_TYPE DO_BUFFERED_IO
#define USE_WRITE_FUNCTION  Example_WriteBufferedIO
#endif

#ifndef IO_TYPE
#define IO_TYPE 0
#define USE_WRITE_FUNCTION  Example_WriteNeither
#endif

#endif


/**********************************************************************
 * Internal Functions
 **********************************************************************/
BOOLEAN Example_IsStringTerminated(PCHAR pString, UINT uiLength);


#pragma alloc_text(PAGE, Example_Create) 
#pragma alloc_text(PAGE, Example_Close) 
#pragma alloc_text(PAGE, Example_IoControl) 
#pragma alloc_text(PAGE, Example_Read)
#pragma alloc_text(PAGE, Example_WriteDirectIO)
#pragma alloc_text(PAGE, Example_WriteBufferedIO)
#pragma alloc_text(PAGE, Example_WriteNeither)
#pragma alloc_text(PAGE, Example_UnSupportedFunction)
#pragma alloc_text(PAGE, Example_IsStringTerminated)




/**********************************************************************
 * 
 *  Example_Create
 *
 *    This is called when an instance of this driver is created (CreateFile)
 *
 **********************************************************************/
NTSTATUS Example_Create(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
    NTSTATUS NtStatus = STATUS_SUCCESS;
    DbgPrint("Example_Create Called \r\n");

    return NtStatus;
}

/**********************************************************************
 * 
 *  Example_Close
 *
 *    This is called when an instance of this driver is closed (CloseHandle)
 *
 **********************************************************************/
NTSTATUS Example_Close(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
    NTSTATUS NtStatus = STATUS_SUCCESS;
    DbgPrint("Example_Close Called \r\n");
	//IoDeleteDevice(DeviceObject);
    return NtStatus;
}



/**********************************************************************
 * 
 *  Example_IoControl
 *
 *    This is called when an IOCTL is issued on the device handle (DeviceIoControl)
 *
 **********************************************************************/
NTSTATUS Example_IoControl(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
    NTSTATUS NtStatus = STATUS_SUCCESS;
    DbgPrint("Example_IoControl Called \r\n");

    return NtStatus;
}



/**********************************************************************
 * 
 *  Example_Read
 *
 *    This is called when a read is issued on the device handle (ReadFile/ReadFileEx)
 *
 **********************************************************************/
NTSTATUS Example_Read(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
    NTSTATUS NtStatus = STATUS_SUCCESS;
    DbgPrint("Example_Read Called \r\n");

    return NtStatus;
}



/**********************************************************************
 * 
 *  Example_WriteDirectIO
 *
 *    This is called when a write is issued on the device handle (WriteFile/WriteFileEx)
 *
 *    This version uses Direct I/O
 *
 **********************************************************************/
NTSTATUS Example_WriteDirectIO(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	//UNREFERENCED_PARAMETER(Irp);
    NTSTATUS NtStatus = STATUS_SUCCESS;
    PIO_STACK_LOCATION pIoStackIrp = NULL;
    PCHAR pWriteDataBuffer;

    DbgPrint("Example_WriteDirectIO Called \r\n");
    
    /*
     * Each time the IRP is passed down the driver stack a new stack location is added
     * specifying certain parameters for the IRP to the driver.
     */
    pIoStackIrp = IoGetCurrentIrpStackLocation(Irp);
    
    if(pIoStackIrp)
    {
        pWriteDataBuffer=(PCHAR) MmGetSystemAddressForMdlSafe(Irp->MdlAddress, NormalPagePriority);
    
        if(pWriteDataBuffer)
        {                             
            /*
             * We need to verify that the string is NULL terminated. Bad things can happen
             * if we access memory not valid while in the Kernel.
             */
           if(Example_IsStringTerminated(pWriteDataBuffer, pIoStackIrp->Parameters.Write.Length))
           {
                DbgPrint(pWriteDataBuffer);
           }
        }
    }

    return NtStatus;
}

/**********************************************************************
 * 
 *  Example_WriteBufferedIO
 *
 *    This is called when a write is issued on the device handle (WriteFile/WriteFileEx)
 *
 *    This version uses Buffered I/O
 *
 **********************************************************************/
NTSTATUS Example_WriteBufferedIO(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
    NTSTATUS NtStatus = STATUS_SUCCESS;
    PIO_STACK_LOCATION pIoStackIrp = NULL;
    PCHAR pWriteDataBuffer;

    DbgPrint("Example_WriteBufferedIO Called \r\n");
    
    /*
     * Each time the IRP is passed down the driver stack a new stack location is added
     * specifying certain parameters for the IRP to the driver.
     */
    pIoStackIrp = IoGetCurrentIrpStackLocation(Irp);
    
    if(pIoStackIrp)
    {
        pWriteDataBuffer = (PCHAR)Irp->AssociatedIrp.SystemBuffer;
    
        if(pWriteDataBuffer)
        {                             
            /*
             * We need to verify that the string is NULL terminated. Bad things can happen
             * if we access memory not valid while in the Kernel.
             */
           if(Example_IsStringTerminated(pWriteDataBuffer, pIoStackIrp->Parameters.Write.Length))
           {
                DbgPrint(pWriteDataBuffer);
           }
        }
    }

    return NtStatus;
}

/**********************************************************************
 * 
 *  Example_WriteNeither
 *
 *    This is called when a write is issued on the device handle (WriteFile/WriteFileEx)
 *
 *    This version uses Neither buffered or direct I/O.  User mode memory is
 *    read directly.
 *
 **********************************************************************/
NTSTATUS Example_WriteNeither(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
    NTSTATUS NtStatus = STATUS_SUCCESS;
    PIO_STACK_LOCATION pIoStackIrp = NULL;
    PCHAR pWriteDataBuffer;

    DbgPrint("Example_WriteNeither Called \r\n");
    
    /*
     * Each time the IRP is passed down the driver stack a new stack location is added
     * specifying certain parameters for the IRP to the driver.
     */
    pIoStackIrp = IoGetCurrentIrpStackLocation(Irp);
    
   


    return NtStatus;
}
                       

/**********************************************************************
 * 
 *  Example_UnSupportedFunction
 *
 *    This is called when a major function is issued that isn't supported.
 *
 **********************************************************************/
NTSTATUS Example_UnSupportedFunction(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
    NTSTATUS NtStatus = STATUS_NOT_SUPPORTED;
    DbgPrint("Example_UnSupportedFunction Called \r\n");

    return NtStatus;
}


/**********************************************************************
 * 
 *  Example_IsStringTerminated
 *
 *    Simple function to determine a string is NULL terminated.
 *
 **** We could validate also the characters in the string are printable! ***
 *
 **********************************************************************/
BOOLEAN Example_IsStringTerminated(PCHAR pString, UINT uiLength)
{
    BOOLEAN bStringIsTerminated = FALSE;
    UINT uiIndex = 0;

    while(uiIndex < uiLength && bStringIsTerminated == FALSE)
    {
        if(pString[uiIndex] == '\0')
        {
            bStringIsTerminated = TRUE;
        }
        else
        {
           uiIndex++;
        }
    }

    return bStringIsTerminated;
}



typedef unsigned int UINT;
void Example_Unload( 
    PDRIVER_OBJECT pDriverObject) 
{  
	//UNICODE_STRING usDosDeviceName;
    DbgPrint("Driver unloading\n"); 

 //   RtlInitUnicodeString(&usDosDeviceName, L"\\DosDevices\\RonilD");
    //IoDeleteSymbolicLink(&usDosDeviceName);

   // IoDeleteDevice(pDriverObject->DeviceObject);
}

NTSTATUS DriverEntry( 
    PDRIVER_OBJECT pDriverObject, 
    PUNICODE_STRING pRegistryPath) 
{ 
	 NTSTATUS NtStatus = STATUS_SUCCESS;
	  UINT uiIndex = 0;
    PDEVICE_OBJECT pDeviceObject = NULL;
    UNICODE_STRING usDriverName, usDosDeviceName;
   // pDriverObject->DriverUnload = DriverUnload; 


    DbgPrint("Hello, World\n"); 
  RtlInitUnicodeString(&usDriverName, L"\\Device\\RonilD");
    RtlInitUnicodeString(&usDosDeviceName, L"\\DosDevices\\RonilD"); 

    NtStatus = IoCreateDevice(pDriverObject, 0, &usDriverName, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &pDeviceObject);

    if(NtStatus == STATUS_SUCCESS)
    {

        /*
         * The "MajorFunction" is a list of function pointers for entry points into the driver.
         * You can set them all to point to 1 function, then have a switch statement for all
         * IRP_MJ_*** functions or you can set specific function pointers for each entry
         * into the driver.
         *
         */
        for(uiIndex = 0; uiIndex < IRP_MJ_MAXIMUM_FUNCTION; uiIndex++)
             pDriverObject->MajorFunction[uiIndex] = Example_UnSupportedFunction;
    
        pDriverObject->MajorFunction[IRP_MJ_CLOSE]             = Example_Close;
        pDriverObject->MajorFunction[IRP_MJ_CREATE]            = Example_Create;
        pDriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL]    = Example_IoControl;
        pDriverObject->MajorFunction[IRP_MJ_READ]              = Example_Read;
        pDriverObject->MajorFunction[IRP_MJ_WRITE]             = USE_WRITE_FUNCTION;
    
        /* 
         * Required to unload the driver dynamically.  If this function is missing
         * the driver cannot be dynamically unloaded.
         */
        pDriverObject->DriverUnload =  Example_Unload; 

       
         
        pDeviceObject->Flags |= IO_TYPE;
    
        /*
         * We are not required to clear this flag in the DriverEntry as the I/O Manager will
         * clear it for us, but we will anyway.  Creating a device in any other location we
         * would need to clear it.
         */
    
        pDeviceObject->Flags &= (~DO_DEVICE_INITIALIZING);
    
        /*
         * Create a Symbolic Link to the device. Example -> \Device\Example
         */
    
        IoCreateSymbolicLink(&usDosDeviceName, &usDriverName);
    }

	//IoDeleteDevice(pDeviceObject);
    return NtStatus;
}