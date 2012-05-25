using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Design;
using System.Windows.Forms.Design;
using System.Net;
namespace BotStudio
{
	class PropertyGridIPAddressInput : UITypeEditor
	{
		IPAddressControlLib.IPAddressControl FAddressControl;

		public override UITypeEditorEditStyle GetEditStyle(System.ComponentModel.ITypeDescriptorContext context)
		{
			return UITypeEditorEditStyle.DropDown;
		}


		public override object EditValue(System.ComponentModel.ITypeDescriptorContext context, System.IServiceProvider provider, object value)
		{
			IWindowsFormsEditorService edSvc = (IWindowsFormsEditorService)provider.GetService(typeof(IWindowsFormsEditorService));

			if (edSvc != null)
			{
				

				FAddressControl = new IPAddressControlLib.IPAddressControl();
				FAddressControl.Text = value.ToString();
				edSvc.DropDownControl(FAddressControl);

				return IPAddress.Parse(FAddressControl.Text);
			}
			return value;
		}
	}
}
