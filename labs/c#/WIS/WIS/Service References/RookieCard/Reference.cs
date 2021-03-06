﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:2.0.50727.3603
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace WIS.RookieCard {
    using System.Runtime.Serialization;
    using System;
    
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Runtime.Serialization", "3.0.0.0")]
    [System.Runtime.Serialization.CollectionDataContractAttribute(Name="ArrayOfString", Namespace="http://yooluck.com/", ItemName="string")]
    [System.SerializableAttribute()]
    public class ArrayOfString : System.Collections.Generic.List<string> {
    }
    
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.ServiceContractAttribute(Namespace="http://yooluck.com/", ConfigurationName="RookieCard.RookieCardSoap")]
    public interface RookieCardSoap {
        
        // CODEGEN: Generating message contract since element name code from namespace http://yooluck.com/ is not marked nillable
        [System.ServiceModel.OperationContractAttribute(Action="http://yooluck.com/UseCard", ReplyAction="*")]
        WIS.RookieCard.UseCardResponse UseCard(WIS.RookieCard.UseCardRequest request);
        
        [System.ServiceModel.OperationContractAttribute(AsyncPattern=true, Action="http://yooluck.com/UseCard", ReplyAction="*")]
        System.IAsyncResult BeginUseCard(WIS.RookieCard.UseCardRequest request, System.AsyncCallback callback, object asyncState);
        
        WIS.RookieCard.UseCardResponse EndUseCard(System.IAsyncResult result);
        
        // CODEGEN: Generating message contract since element name GenerateCardResult from namespace http://yooluck.com/ is not marked nillable
        [System.ServiceModel.OperationContractAttribute(Action="http://yooluck.com/GenerateCard", ReplyAction="*")]
        WIS.RookieCard.GenerateCardResponse GenerateCard(WIS.RookieCard.GenerateCardRequest request);
        
        [System.ServiceModel.OperationContractAttribute(AsyncPattern=true, Action="http://yooluck.com/GenerateCard", ReplyAction="*")]
        System.IAsyncResult BeginGenerateCard(WIS.RookieCard.GenerateCardRequest request, System.AsyncCallback callback, object asyncState);
        
        WIS.RookieCard.GenerateCardResponse EndGenerateCard(System.IAsyncResult result);
        
        // CODEGEN: Generating message contract since element name GenerateCardsResult from namespace http://yooluck.com/ is not marked nillable
        [System.ServiceModel.OperationContractAttribute(Action="http://yooluck.com/GenerateCards", ReplyAction="*")]
        WIS.RookieCard.GenerateCardsResponse GenerateCards(WIS.RookieCard.GenerateCardsRequest request);
        
        [System.ServiceModel.OperationContractAttribute(AsyncPattern=true, Action="http://yooluck.com/GenerateCards", ReplyAction="*")]
        System.IAsyncResult BeginGenerateCards(WIS.RookieCard.GenerateCardsRequest request, System.AsyncCallback callback, object asyncState);
        
        WIS.RookieCard.GenerateCardsResponse EndGenerateCards(System.IAsyncResult result);
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.MessageContractAttribute(IsWrapped=false)]
    public partial class UseCardRequest {
        
        [System.ServiceModel.MessageBodyMemberAttribute(Name="UseCard", Namespace="http://yooluck.com/", Order=0)]
        public WIS.RookieCard.UseCardRequestBody Body;
        
        public UseCardRequest() {
        }
        
        public UseCardRequest(WIS.RookieCard.UseCardRequestBody Body) {
            this.Body = Body;
        }
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.Runtime.Serialization.DataContractAttribute(Namespace="http://yooluck.com/")]
    public partial class UseCardRequestBody {
        
        [System.Runtime.Serialization.DataMemberAttribute(EmitDefaultValue=false, Order=0)]
        public string code;
        
        [System.Runtime.Serialization.DataMemberAttribute(Order=1)]
        public int regionId;
        
        [System.Runtime.Serialization.DataMemberAttribute(Order=2)]
        public int partnerId;
        
        public UseCardRequestBody() {
        }
        
        public UseCardRequestBody(string code, int regionId, int partnerId) {
            this.code = code;
            this.regionId = regionId;
            this.partnerId = partnerId;
        }
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.MessageContractAttribute(IsWrapped=false)]
    public partial class UseCardResponse {
        
        [System.ServiceModel.MessageBodyMemberAttribute(Name="UseCardResponse", Namespace="http://yooluck.com/", Order=0)]
        public WIS.RookieCard.UseCardResponseBody Body;
        
        public UseCardResponse() {
        }
        
        public UseCardResponse(WIS.RookieCard.UseCardResponseBody Body) {
            this.Body = Body;
        }
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.Runtime.Serialization.DataContractAttribute(Namespace="http://yooluck.com/")]
    public partial class UseCardResponseBody {
        
        [System.Runtime.Serialization.DataMemberAttribute(Order=0)]
        public byte UseCardResult;
        
        [System.Runtime.Serialization.DataMemberAttribute(Order=1)]
        public uint itemTemplate;
        
        public UseCardResponseBody() {
        }
        
        public UseCardResponseBody(byte UseCardResult, uint itemTemplate) {
            this.UseCardResult = UseCardResult;
            this.itemTemplate = itemTemplate;
        }
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.MessageContractAttribute(IsWrapped=false)]
    public partial class GenerateCardRequest {
        
        [System.ServiceModel.MessageBodyMemberAttribute(Name="GenerateCard", Namespace="http://yooluck.com/", Order=0)]
        public WIS.RookieCard.GenerateCardRequestBody Body;
        
        public GenerateCardRequest() {
        }
        
        public GenerateCardRequest(WIS.RookieCard.GenerateCardRequestBody Body) {
            this.Body = Body;
        }
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.Runtime.Serialization.DataContractAttribute(Namespace="http://yooluck.com/")]
    public partial class GenerateCardRequestBody {
        
        [System.Runtime.Serialization.DataMemberAttribute(Order=0)]
        public int generation;
        
        [System.Runtime.Serialization.DataMemberAttribute(Order=1)]
        public int region_id;
        
        [System.Runtime.Serialization.DataMemberAttribute(Order=2)]
        public int partner_id;
        
        [System.Runtime.Serialization.DataMemberAttribute(Order=3)]
        public System.DateTime expire;
        
        public GenerateCardRequestBody() {
        }
        
        public GenerateCardRequestBody(int generation, int region_id, int partner_id, System.DateTime expire) {
            this.generation = generation;
            this.region_id = region_id;
            this.partner_id = partner_id;
            this.expire = expire;
        }
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.MessageContractAttribute(IsWrapped=false)]
    public partial class GenerateCardResponse {
        
        [System.ServiceModel.MessageBodyMemberAttribute(Name="GenerateCardResponse", Namespace="http://yooluck.com/", Order=0)]
        public WIS.RookieCard.GenerateCardResponseBody Body;
        
        public GenerateCardResponse() {
        }
        
        public GenerateCardResponse(WIS.RookieCard.GenerateCardResponseBody Body) {
            this.Body = Body;
        }
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.Runtime.Serialization.DataContractAttribute(Namespace="http://yooluck.com/")]
    public partial class GenerateCardResponseBody {
        
        [System.Runtime.Serialization.DataMemberAttribute(EmitDefaultValue=false, Order=0)]
        public string GenerateCardResult;
        
        public GenerateCardResponseBody() {
        }
        
        public GenerateCardResponseBody(string GenerateCardResult) {
            this.GenerateCardResult = GenerateCardResult;
        }
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.MessageContractAttribute(IsWrapped=false)]
    public partial class GenerateCardsRequest {
        
        [System.ServiceModel.MessageBodyMemberAttribute(Name="GenerateCards", Namespace="http://yooluck.com/", Order=0)]
        public WIS.RookieCard.GenerateCardsRequestBody Body;
        
        public GenerateCardsRequest() {
        }
        
        public GenerateCardsRequest(WIS.RookieCard.GenerateCardsRequestBody Body) {
            this.Body = Body;
        }
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.Runtime.Serialization.DataContractAttribute(Namespace="http://yooluck.com/")]
    public partial class GenerateCardsRequestBody {
        
        [System.Runtime.Serialization.DataMemberAttribute(Order=0)]
        public int count;
        
        [System.Runtime.Serialization.DataMemberAttribute(Order=1)]
        public int generation;
        
        [System.Runtime.Serialization.DataMemberAttribute(Order=2)]
        public int region_id;
        
        [System.Runtime.Serialization.DataMemberAttribute(Order=3)]
        public int partner_id;
        
        [System.Runtime.Serialization.DataMemberAttribute(Order=4)]
        public System.DateTime expire;
        
        public GenerateCardsRequestBody() {
        }
        
        public GenerateCardsRequestBody(int count, int generation, int region_id, int partner_id, System.DateTime expire) {
            this.count = count;
            this.generation = generation;
            this.region_id = region_id;
            this.partner_id = partner_id;
            this.expire = expire;
        }
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.MessageContractAttribute(IsWrapped=false)]
    public partial class GenerateCardsResponse {
        
        [System.ServiceModel.MessageBodyMemberAttribute(Name="GenerateCardsResponse", Namespace="http://yooluck.com/", Order=0)]
        public WIS.RookieCard.GenerateCardsResponseBody Body;
        
        public GenerateCardsResponse() {
        }
        
        public GenerateCardsResponse(WIS.RookieCard.GenerateCardsResponseBody Body) {
            this.Body = Body;
        }
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.Runtime.Serialization.DataContractAttribute(Namespace="http://yooluck.com/")]
    public partial class GenerateCardsResponseBody {
        
        [System.Runtime.Serialization.DataMemberAttribute(EmitDefaultValue=false, Order=0)]
        public WIS.RookieCard.ArrayOfString GenerateCardsResult;
        
        public GenerateCardsResponseBody() {
        }
        
        public GenerateCardsResponseBody(WIS.RookieCard.ArrayOfString GenerateCardsResult) {
            this.GenerateCardsResult = GenerateCardsResult;
        }
    }
    
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    public interface RookieCardSoapChannel : WIS.RookieCard.RookieCardSoap, System.ServiceModel.IClientChannel {
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    public partial class UseCardCompletedEventArgs : System.ComponentModel.AsyncCompletedEventArgs {
        
        private object[] results;
        
        public UseCardCompletedEventArgs(object[] results, System.Exception exception, bool cancelled, object userState) : 
                base(exception, cancelled, userState) {
            this.results = results;
        }
        
        public uint itemTemplate {
            get {
                base.RaiseExceptionIfNecessary();
                return ((uint)(this.results[0]));
            }
        }
        
        public byte Result {
            get {
                base.RaiseExceptionIfNecessary();
                return ((byte)(this.results[1]));
            }
        }
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    public partial class GenerateCardCompletedEventArgs : System.ComponentModel.AsyncCompletedEventArgs {
        
        private object[] results;
        
        public GenerateCardCompletedEventArgs(object[] results, System.Exception exception, bool cancelled, object userState) : 
                base(exception, cancelled, userState) {
            this.results = results;
        }
        
        public string Result {
            get {
                base.RaiseExceptionIfNecessary();
                return ((string)(this.results[0]));
            }
        }
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    public partial class GenerateCardsCompletedEventArgs : System.ComponentModel.AsyncCompletedEventArgs {
        
        private object[] results;
        
        public GenerateCardsCompletedEventArgs(object[] results, System.Exception exception, bool cancelled, object userState) : 
                base(exception, cancelled, userState) {
            this.results = results;
        }
        
        public WIS.RookieCard.ArrayOfString Result {
            get {
                base.RaiseExceptionIfNecessary();
                return ((WIS.RookieCard.ArrayOfString)(this.results[0]));
            }
        }
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    public partial class RookieCardSoapClient : System.ServiceModel.ClientBase<WIS.RookieCard.RookieCardSoap>, WIS.RookieCard.RookieCardSoap {
        
        private BeginOperationDelegate onBeginUseCardDelegate;
        
        private EndOperationDelegate onEndUseCardDelegate;
        
        private System.Threading.SendOrPostCallback onUseCardCompletedDelegate;
        
        private BeginOperationDelegate onBeginGenerateCardDelegate;
        
        private EndOperationDelegate onEndGenerateCardDelegate;
        
        private System.Threading.SendOrPostCallback onGenerateCardCompletedDelegate;
        
        private BeginOperationDelegate onBeginGenerateCardsDelegate;
        
        private EndOperationDelegate onEndGenerateCardsDelegate;
        
        private System.Threading.SendOrPostCallback onGenerateCardsCompletedDelegate;
        
        public RookieCardSoapClient() {
        }
        
        public RookieCardSoapClient(string endpointConfigurationName) : 
                base(endpointConfigurationName) {
        }
        
        public RookieCardSoapClient(string endpointConfigurationName, string remoteAddress) : 
                base(endpointConfigurationName, remoteAddress) {
        }
        
        public RookieCardSoapClient(string endpointConfigurationName, System.ServiceModel.EndpointAddress remoteAddress) : 
                base(endpointConfigurationName, remoteAddress) {
        }
        
        public RookieCardSoapClient(System.ServiceModel.Channels.Binding binding, System.ServiceModel.EndpointAddress remoteAddress) : 
                base(binding, remoteAddress) {
        }
        
        public event System.EventHandler<UseCardCompletedEventArgs> UseCardCompleted;
        
        public event System.EventHandler<GenerateCardCompletedEventArgs> GenerateCardCompleted;
        
        public event System.EventHandler<GenerateCardsCompletedEventArgs> GenerateCardsCompleted;
        
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        WIS.RookieCard.UseCardResponse WIS.RookieCard.RookieCardSoap.UseCard(WIS.RookieCard.UseCardRequest request) {
            return base.Channel.UseCard(request);
        }
        
        public byte UseCard(string code, int regionId, int partnerId, out uint itemTemplate) {
            WIS.RookieCard.UseCardRequest inValue = new WIS.RookieCard.UseCardRequest();
            inValue.Body = new WIS.RookieCard.UseCardRequestBody();
            inValue.Body.code = code;
            inValue.Body.regionId = regionId;
            inValue.Body.partnerId = partnerId;
            WIS.RookieCard.UseCardResponse retVal = ((WIS.RookieCard.RookieCardSoap)(this)).UseCard(inValue);
            itemTemplate = retVal.Body.itemTemplate;
            return retVal.Body.UseCardResult;
        }
        
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        System.IAsyncResult WIS.RookieCard.RookieCardSoap.BeginUseCard(WIS.RookieCard.UseCardRequest request, System.AsyncCallback callback, object asyncState) {
            return base.Channel.BeginUseCard(request, callback, asyncState);
        }
        
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        public System.IAsyncResult BeginUseCard(string code, int regionId, int partnerId, System.AsyncCallback callback, object asyncState) {
            WIS.RookieCard.UseCardRequest inValue = new WIS.RookieCard.UseCardRequest();
            inValue.Body = new WIS.RookieCard.UseCardRequestBody();
            inValue.Body.code = code;
            inValue.Body.regionId = regionId;
            inValue.Body.partnerId = partnerId;
            return ((WIS.RookieCard.RookieCardSoap)(this)).BeginUseCard(inValue, callback, asyncState);
        }
        
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        WIS.RookieCard.UseCardResponse WIS.RookieCard.RookieCardSoap.EndUseCard(System.IAsyncResult result) {
            return base.Channel.EndUseCard(result);
        }
        
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        public byte EndUseCard(System.IAsyncResult result, out uint itemTemplate) {
            WIS.RookieCard.UseCardResponse retVal = ((WIS.RookieCard.RookieCardSoap)(this)).EndUseCard(result);
            itemTemplate = retVal.Body.itemTemplate;
            return retVal.Body.UseCardResult;
        }
        
        private System.IAsyncResult OnBeginUseCard(object[] inValues, System.AsyncCallback callback, object asyncState) {
            string code = ((string)(inValues[0]));
            int regionId = ((int)(inValues[1]));
            int partnerId = ((int)(inValues[2]));
            return this.BeginUseCard(code, regionId, partnerId, callback, asyncState);
        }
        
        private object[] OnEndUseCard(System.IAsyncResult result) {
            uint itemTemplate = this.GetDefaultValueForInitialization<uint>();
            byte retVal = this.EndUseCard(result, out itemTemplate);
            return new object[] {
                    itemTemplate,
                    retVal};
        }
        
        private void OnUseCardCompleted(object state) {
            if ((this.UseCardCompleted != null)) {
                InvokeAsyncCompletedEventArgs e = ((InvokeAsyncCompletedEventArgs)(state));
                this.UseCardCompleted(this, new UseCardCompletedEventArgs(e.Results, e.Error, e.Cancelled, e.UserState));
            }
        }
        
        public void UseCardAsync(string code, int regionId, int partnerId) {
            this.UseCardAsync(code, regionId, partnerId, null);
        }
        
        public void UseCardAsync(string code, int regionId, int partnerId, object userState) {
            if ((this.onBeginUseCardDelegate == null)) {
                this.onBeginUseCardDelegate = new BeginOperationDelegate(this.OnBeginUseCard);
            }
            if ((this.onEndUseCardDelegate == null)) {
                this.onEndUseCardDelegate = new EndOperationDelegate(this.OnEndUseCard);
            }
            if ((this.onUseCardCompletedDelegate == null)) {
                this.onUseCardCompletedDelegate = new System.Threading.SendOrPostCallback(this.OnUseCardCompleted);
            }
            base.InvokeAsync(this.onBeginUseCardDelegate, new object[] {
                        code,
                        regionId,
                        partnerId}, this.onEndUseCardDelegate, this.onUseCardCompletedDelegate, userState);
        }
        
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        WIS.RookieCard.GenerateCardResponse WIS.RookieCard.RookieCardSoap.GenerateCard(WIS.RookieCard.GenerateCardRequest request) {
            return base.Channel.GenerateCard(request);
        }
        
        public string GenerateCard(int generation, int region_id, int partner_id, System.DateTime expire) {
            WIS.RookieCard.GenerateCardRequest inValue = new WIS.RookieCard.GenerateCardRequest();
            inValue.Body = new WIS.RookieCard.GenerateCardRequestBody();
            inValue.Body.generation = generation;
            inValue.Body.region_id = region_id;
            inValue.Body.partner_id = partner_id;
            inValue.Body.expire = expire;
            WIS.RookieCard.GenerateCardResponse retVal = ((WIS.RookieCard.RookieCardSoap)(this)).GenerateCard(inValue);
            return retVal.Body.GenerateCardResult;
        }
        
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        System.IAsyncResult WIS.RookieCard.RookieCardSoap.BeginGenerateCard(WIS.RookieCard.GenerateCardRequest request, System.AsyncCallback callback, object asyncState) {
            return base.Channel.BeginGenerateCard(request, callback, asyncState);
        }
        
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        public System.IAsyncResult BeginGenerateCard(int generation, int region_id, int partner_id, System.DateTime expire, System.AsyncCallback callback, object asyncState) {
            WIS.RookieCard.GenerateCardRequest inValue = new WIS.RookieCard.GenerateCardRequest();
            inValue.Body = new WIS.RookieCard.GenerateCardRequestBody();
            inValue.Body.generation = generation;
            inValue.Body.region_id = region_id;
            inValue.Body.partner_id = partner_id;
            inValue.Body.expire = expire;
            return ((WIS.RookieCard.RookieCardSoap)(this)).BeginGenerateCard(inValue, callback, asyncState);
        }
        
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        WIS.RookieCard.GenerateCardResponse WIS.RookieCard.RookieCardSoap.EndGenerateCard(System.IAsyncResult result) {
            return base.Channel.EndGenerateCard(result);
        }
        
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        public string EndGenerateCard(System.IAsyncResult result) {
            WIS.RookieCard.GenerateCardResponse retVal = ((WIS.RookieCard.RookieCardSoap)(this)).EndGenerateCard(result);
            return retVal.Body.GenerateCardResult;
        }
        
        private System.IAsyncResult OnBeginGenerateCard(object[] inValues, System.AsyncCallback callback, object asyncState) {
            int generation = ((int)(inValues[0]));
            int region_id = ((int)(inValues[1]));
            int partner_id = ((int)(inValues[2]));
            System.DateTime expire = ((System.DateTime)(inValues[3]));
            return this.BeginGenerateCard(generation, region_id, partner_id, expire, callback, asyncState);
        }
        
        private object[] OnEndGenerateCard(System.IAsyncResult result) {
            string retVal = this.EndGenerateCard(result);
            return new object[] {
                    retVal};
        }
        
        private void OnGenerateCardCompleted(object state) {
            if ((this.GenerateCardCompleted != null)) {
                InvokeAsyncCompletedEventArgs e = ((InvokeAsyncCompletedEventArgs)(state));
                this.GenerateCardCompleted(this, new GenerateCardCompletedEventArgs(e.Results, e.Error, e.Cancelled, e.UserState));
            }
        }
        
        public void GenerateCardAsync(int generation, int region_id, int partner_id, System.DateTime expire) {
            this.GenerateCardAsync(generation, region_id, partner_id, expire, null);
        }
        
        public void GenerateCardAsync(int generation, int region_id, int partner_id, System.DateTime expire, object userState) {
            if ((this.onBeginGenerateCardDelegate == null)) {
                this.onBeginGenerateCardDelegate = new BeginOperationDelegate(this.OnBeginGenerateCard);
            }
            if ((this.onEndGenerateCardDelegate == null)) {
                this.onEndGenerateCardDelegate = new EndOperationDelegate(this.OnEndGenerateCard);
            }
            if ((this.onGenerateCardCompletedDelegate == null)) {
                this.onGenerateCardCompletedDelegate = new System.Threading.SendOrPostCallback(this.OnGenerateCardCompleted);
            }
            base.InvokeAsync(this.onBeginGenerateCardDelegate, new object[] {
                        generation,
                        region_id,
                        partner_id,
                        expire}, this.onEndGenerateCardDelegate, this.onGenerateCardCompletedDelegate, userState);
        }
        
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        WIS.RookieCard.GenerateCardsResponse WIS.RookieCard.RookieCardSoap.GenerateCards(WIS.RookieCard.GenerateCardsRequest request) {
            return base.Channel.GenerateCards(request);
        }
        
        public WIS.RookieCard.ArrayOfString GenerateCards(int count, int generation, int region_id, int partner_id, System.DateTime expire) {
            WIS.RookieCard.GenerateCardsRequest inValue = new WIS.RookieCard.GenerateCardsRequest();
            inValue.Body = new WIS.RookieCard.GenerateCardsRequestBody();
            inValue.Body.count = count;
            inValue.Body.generation = generation;
            inValue.Body.region_id = region_id;
            inValue.Body.partner_id = partner_id;
            inValue.Body.expire = expire;
            WIS.RookieCard.GenerateCardsResponse retVal = ((WIS.RookieCard.RookieCardSoap)(this)).GenerateCards(inValue);
            return retVal.Body.GenerateCardsResult;
        }
        
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        System.IAsyncResult WIS.RookieCard.RookieCardSoap.BeginGenerateCards(WIS.RookieCard.GenerateCardsRequest request, System.AsyncCallback callback, object asyncState) {
            return base.Channel.BeginGenerateCards(request, callback, asyncState);
        }
        
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        public System.IAsyncResult BeginGenerateCards(int count, int generation, int region_id, int partner_id, System.DateTime expire, System.AsyncCallback callback, object asyncState) {
            WIS.RookieCard.GenerateCardsRequest inValue = new WIS.RookieCard.GenerateCardsRequest();
            inValue.Body = new WIS.RookieCard.GenerateCardsRequestBody();
            inValue.Body.count = count;
            inValue.Body.generation = generation;
            inValue.Body.region_id = region_id;
            inValue.Body.partner_id = partner_id;
            inValue.Body.expire = expire;
            return ((WIS.RookieCard.RookieCardSoap)(this)).BeginGenerateCards(inValue, callback, asyncState);
        }
        
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        WIS.RookieCard.GenerateCardsResponse WIS.RookieCard.RookieCardSoap.EndGenerateCards(System.IAsyncResult result) {
            return base.Channel.EndGenerateCards(result);
        }
        
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        public WIS.RookieCard.ArrayOfString EndGenerateCards(System.IAsyncResult result) {
            WIS.RookieCard.GenerateCardsResponse retVal = ((WIS.RookieCard.RookieCardSoap)(this)).EndGenerateCards(result);
            return retVal.Body.GenerateCardsResult;
        }
        
        private System.IAsyncResult OnBeginGenerateCards(object[] inValues, System.AsyncCallback callback, object asyncState) {
            int count = ((int)(inValues[0]));
            int generation = ((int)(inValues[1]));
            int region_id = ((int)(inValues[2]));
            int partner_id = ((int)(inValues[3]));
            System.DateTime expire = ((System.DateTime)(inValues[4]));
            return this.BeginGenerateCards(count, generation, region_id, partner_id, expire, callback, asyncState);
        }
        
        private object[] OnEndGenerateCards(System.IAsyncResult result) {
            WIS.RookieCard.ArrayOfString retVal = this.EndGenerateCards(result);
            return new object[] {
                    retVal};
        }
        
        private void OnGenerateCardsCompleted(object state) {
            if ((this.GenerateCardsCompleted != null)) {
                InvokeAsyncCompletedEventArgs e = ((InvokeAsyncCompletedEventArgs)(state));
                this.GenerateCardsCompleted(this, new GenerateCardsCompletedEventArgs(e.Results, e.Error, e.Cancelled, e.UserState));
            }
        }
        
        public void GenerateCardsAsync(int count, int generation, int region_id, int partner_id, System.DateTime expire) {
            this.GenerateCardsAsync(count, generation, region_id, partner_id, expire, null);
        }
        
        public void GenerateCardsAsync(int count, int generation, int region_id, int partner_id, System.DateTime expire, object userState) {
            if ((this.onBeginGenerateCardsDelegate == null)) {
                this.onBeginGenerateCardsDelegate = new BeginOperationDelegate(this.OnBeginGenerateCards);
            }
            if ((this.onEndGenerateCardsDelegate == null)) {
                this.onEndGenerateCardsDelegate = new EndOperationDelegate(this.OnEndGenerateCards);
            }
            if ((this.onGenerateCardsCompletedDelegate == null)) {
                this.onGenerateCardsCompletedDelegate = new System.Threading.SendOrPostCallback(this.OnGenerateCardsCompleted);
            }
            base.InvokeAsync(this.onBeginGenerateCardsDelegate, new object[] {
                        count,
                        generation,
                        region_id,
                        partner_id,
                        expire}, this.onEndGenerateCardsDelegate, this.onGenerateCardsCompletedDelegate, userState);
        }
    }
}
