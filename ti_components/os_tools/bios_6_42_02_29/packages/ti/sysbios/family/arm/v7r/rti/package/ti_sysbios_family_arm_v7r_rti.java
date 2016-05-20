/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-A71
 */
import java.util.*;
import org.mozilla.javascript.*;
import xdc.services.intern.xsr.*;
import xdc.services.spec.Session;

public class ti_sysbios_family_arm_v7r_rti
{
    static final String VERS = "@(#) xdc-A71\n";

    static final Proto.Elm $$T_Bool = Proto.Elm.newBool();
    static final Proto.Elm $$T_Num = Proto.Elm.newNum();
    static final Proto.Elm $$T_Str = Proto.Elm.newStr();
    static final Proto.Elm $$T_Obj = Proto.Elm.newObj();

    static final Proto.Fxn $$T_Met = new Proto.Fxn(null, null, 0, -1, false);
    static final Proto.Map $$T_Map = new Proto.Map($$T_Obj);
    static final Proto.Arr $$T_Vec = new Proto.Arr($$T_Obj);

    static final XScriptO $$DEFAULT = Value.DEFAULT;
    static final Object $$UNDEF = Undefined.instance;

    static final Proto.Obj $$Package = (Proto.Obj)Global.get("$$Package");
    static final Proto.Obj $$Module = (Proto.Obj)Global.get("$$Module");
    static final Proto.Obj $$Instance = (Proto.Obj)Global.get("$$Instance");
    static final Proto.Obj $$Params = (Proto.Obj)Global.get("$$Params");

    static final Object $$objFldGet = Global.get("$$objFldGet");
    static final Object $$objFldSet = Global.get("$$objFldSet");
    static final Object $$proxyGet = Global.get("$$proxyGet");
    static final Object $$proxySet = Global.get("$$proxySet");
    static final Object $$delegGet = Global.get("$$delegGet");
    static final Object $$delegSet = Global.get("$$delegSet");

    Scriptable xdcO;
    Session ses;
    Value.Obj om;

    boolean isROV;
    boolean isCFG;

    Proto.Obj pkgP;
    Value.Obj pkgV;

    ArrayList<Object> imports = new ArrayList<Object>();
    ArrayList<Object> loggables = new ArrayList<Object>();
    ArrayList<Object> mcfgs = new ArrayList<Object>();
    ArrayList<Object> icfgs = new ArrayList<Object>();
    ArrayList<String> inherits = new ArrayList<String>();
    ArrayList<Object> proxies = new ArrayList<Object>();
    ArrayList<Object> sizes = new ArrayList<Object>();
    ArrayList<Object> tdefs = new ArrayList<Object>();

    void $$IMPORTS()
    {
        Global.callFxn("loadPackage", xdcO, "ti.sysbios.interfaces");
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
        Global.callFxn("loadPackage", xdcO, "xdc.rov");
        Global.callFxn("loadPackage", xdcO, "xdc.runtime");
        Global.callFxn("loadPackage", xdcO, "ti.sysbios.family.arm.v7r.vim");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.sysbios.family.arm.v7r.rti.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.sysbios.family.arm.v7r.rti", new Value.Obj("ti.sysbios.family.arm.v7r.rti", pkgP));
    }

    void Timer$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.sysbios.family.arm.v7r.rti.Timer.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.sysbios.family.arm.v7r.rti.Timer", new Value.Obj("ti.sysbios.family.arm.v7r.rti.Timer", po));
        pkgV.bind("Timer", vo);
        // decls 
        om.bind("ti.sysbios.family.arm.v7r.rti.Timer.StartMode", om.findStrict("ti.sysbios.interfaces.ITimer.StartMode", "ti.sysbios.family.arm.v7r.rti"));
        om.bind("ti.sysbios.family.arm.v7r.rti.Timer.RunMode", om.findStrict("ti.sysbios.interfaces.ITimer.RunMode", "ti.sysbios.family.arm.v7r.rti"));
        om.bind("ti.sysbios.family.arm.v7r.rti.Timer.Status", om.findStrict("ti.sysbios.interfaces.ITimer.Status", "ti.sysbios.family.arm.v7r.rti"));
        om.bind("ti.sysbios.family.arm.v7r.rti.Timer.PeriodType", om.findStrict("ti.sysbios.interfaces.ITimer.PeriodType", "ti.sysbios.family.arm.v7r.rti"));
        spo = (Proto.Obj)om.bind("ti.sysbios.family.arm.v7r.rti.Timer$$BasicView", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v7r.rti.Timer.BasicView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sysbios.family.arm.v7r.rti.Timer$$DeviceView", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v7r.rti.Timer.DeviceView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sysbios.family.arm.v7r.rti.Timer$$ModuleView", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v7r.rti.Timer.ModuleView", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sysbios.family.arm.v7r.rti.Timer$$DeviceRegs", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v7r.rti.Timer.DeviceRegs", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sysbios.family.arm.v7r.rti.Timer$$Instance_State", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v7r.rti.Timer.Instance_State", new Proto.Str(spo, false));
        spo = (Proto.Obj)om.bind("ti.sysbios.family.arm.v7r.rti.Timer$$Module_State", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v7r.rti.Timer.Module_State", new Proto.Str(spo, false));
        // insts 
        Object insP = om.bind("ti.sysbios.family.arm.v7r.rti.Timer.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("ti.sysbios.family.arm.v7r.rti.Timer$$Object", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v7r.rti.Timer.Object", new Proto.Str(po, false));
        po = (Proto.Obj)om.bind("ti.sysbios.family.arm.v7r.rti.Timer$$Params", new Proto.Obj());
        om.bind("ti.sysbios.family.arm.v7r.rti.Timer.Params", new Proto.Str(po, false));
        om.bind("ti.sysbios.family.arm.v7r.rti.Timer.Handle", insP);
        if (isROV) {
            om.bind("ti.sysbios.family.arm.v7r.rti.Timer.Object", om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.Instance_State", "ti.sysbios.family.arm.v7r.rti"));
        }//isROV
    }

    void Timer$$CONSTS()
    {
        // module Timer
        om.bind("ti.sysbios.family.arm.v7r.rti.Timer.MAX_PERIOD", 0xffffffffL);
        om.bind("ti.sysbios.family.arm.v7r.rti.Timer.NUM_TIMER_DEVICES", 2L);
        om.bind("ti.sysbios.family.arm.v7r.rti.Timer.MIN_SWEEP_PERIOD", 8L);
        om.bind("ti.sysbios.family.arm.v7r.rti.Timer.deviceRegs", new Extern("ti_sysbios_family_arm_v7r_rti_Timer_deviceRegs", "ti_sysbios_family_arm_v7r_rti_Timer_DeviceRegs*", false, false));
        om.bind("ti.sysbios.family.arm.v7r.rti.Timer.getNumTimers", new Extern("ti_sysbios_family_arm_v7r_rti_Timer_getNumTimers__E", "xdc_UInt(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v7r.rti.Timer.getStatus", new Extern("ti_sysbios_family_arm_v7r_rti_Timer_getStatus__E", "ti_sysbios_interfaces_ITimer_Status(*)(xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v7r.rti.Timer.startup", new Extern("ti_sysbios_family_arm_v7r_rti_Timer_startup__E", "xdc_Void(*)(xdc_Void)", true, false));
        om.bind("ti.sysbios.family.arm.v7r.rti.Timer.oneShotStub", new Extern("ti_sysbios_family_arm_v7r_rti_Timer_oneShotStub__E", "xdc_Void(*)(xdc_UArg)", true, false));
        om.bind("ti.sysbios.family.arm.v7r.rti.Timer.periodicStub", new Extern("ti_sysbios_family_arm_v7r_rti_Timer_periodicStub__E", "xdc_Void(*)(xdc_UArg)", true, false));
        om.bind("ti.sysbios.family.arm.v7r.rti.Timer.getHandle", new Extern("ti_sysbios_family_arm_v7r_rti_Timer_getHandle__E", "ti_sysbios_family_arm_v7r_rti_Timer_Handle(*)(xdc_UInt)", true, false));
        om.bind("ti.sysbios.family.arm.v7r.rti.Timer.initDevice", new Extern("ti_sysbios_family_arm_v7r_rti_Timer_initDevice__I", "xdc_Void(*)(ti_sysbios_family_arm_v7r_rti_Timer_Object*)", true, false));
        om.bind("ti.sysbios.family.arm.v7r.rti.Timer.postInit", new Extern("ti_sysbios_family_arm_v7r_rti_Timer_postInit__I", "xdc_Int(*)(ti_sysbios_family_arm_v7r_rti_Timer_Object*,xdc_runtime_Error_Block*)", true, false));
        om.bind("ti.sysbios.family.arm.v7r.rti.Timer.checkOverflow", new Extern("ti_sysbios_family_arm_v7r_rti_Timer_checkOverflow__I", "xdc_Bool(*)(xdc_UInt32,xdc_UInt32)", true, false));
    }

    void Timer$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        if (isCFG) {
            sb = new StringBuilder();
            sb.append("ti$sysbios$family$arm$v7r$rti$Timer$$__initObject = function( inst ) {\n");
                sb.append("if (!this.$used) {\n");
                    sb.append("throw new Error(\"Function ti.sysbios.family.arm.v7r.rti.Timer.create() called before xdc.useModule('ti.sysbios.family.arm.v7r.rti.Timer')\");\n");
                sb.append("}\n");
                sb.append("var name = xdc.module('xdc.runtime.Text').defineRopeCord(inst.instance.name);\n");
                sb.append("inst.$object.$$bind('__name', name);\n");
                sb.append("this.instance$static$init.$fxn.apply(inst, [inst.$object, inst.$args.id, inst.$args.tickFxn, inst, inst.$module]);\n");
                sb.append("inst.$seal();\n");
            sb.append("};\n");
            Global.eval(sb.toString());
            fxn = (Proto.Fxn)om.bind("ti.sysbios.family.arm.v7r.rti.Timer$$create", new Proto.Fxn(om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.Module", "ti.sysbios.family.arm.v7r.rti"), om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.Instance", "ti.sysbios.family.arm.v7r.rti"), 3, 2, false));
                        fxn.addArg(0, "id", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF);
                        fxn.addArg(1, "tickFxn", new Proto.Adr("xdc_Void(*)(xdc_UArg)", "PFv"), $$UNDEF);
                        fxn.addArg(2, "__params", (Proto)om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.Params", "ti.sysbios.family.arm.v7r.rti"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sysbios$family$arm$v7r$rti$Timer$$create = function( id, tickFxn, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sysbios.family.arm.v7r.rti.Timer'];\n");
                sb.append("var __inst = xdc.om['ti.sysbios.family.arm.v7r.rti.Timer.Instance'].$$make();\n");
                sb.append("__inst.$$bind('$package', xdc.om['ti.sysbios.family.arm.v7r.rti']);\n");
                sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
                sb.append("__inst.$$bind('$category', 'Instance');\n");
                sb.append("__inst.$$bind('$args', {id:id, tickFxn:tickFxn});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$instances.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', new xdc.om['ti.sysbios.family.arm.v7r.rti.Timer'].Instance_State);\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("var save = xdc.om.$curpkg;\n");
                sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
                sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [id, tickFxn]);\n");
                sb.append("xdc.om.$$bind('$curpkg', save);\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sysbios.family.arm.v7r.rti.Timer'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return __inst;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
        if (isCFG) {
            fxn = (Proto.Fxn)om.bind("ti.sysbios.family.arm.v7r.rti.Timer$$construct", new Proto.Fxn(om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.Module", "ti.sysbios.family.arm.v7r.rti"), null, 4, 2, false));
                        fxn.addArg(0, "__obj", (Proto)om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer$$Object", "ti.sysbios.family.arm.v7r.rti"), null);
                        fxn.addArg(1, "id", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF);
                        fxn.addArg(2, "tickFxn", new Proto.Adr("xdc_Void(*)(xdc_UArg)", "PFv"), $$UNDEF);
                        fxn.addArg(3, "__params", (Proto)om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.Params", "ti.sysbios.family.arm.v7r.rti"), Global.newObject());
            sb = new StringBuilder();
            sb.append("ti$sysbios$family$arm$v7r$rti$Timer$$construct = function( __obj, id, tickFxn, __params ) {\n");
                sb.append("var __mod = xdc.om['ti.sysbios.family.arm.v7r.rti.Timer'];\n");
                sb.append("var __inst = __obj;\n");
                sb.append("__inst.$$bind('$args', {id:id, tickFxn:tickFxn});\n");
                sb.append("__inst.$$bind('$module', __mod);\n");
                sb.append("__mod.$objects.$add(__inst);\n");
                sb.append("__inst.$$bind('$object', xdc.om['ti.sysbios.family.arm.v7r.rti.Timer'].Instance_State.$$make(__inst.$$parent, __inst.$name));\n");
                sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
                sb.append("__inst.$$bless();\n");
                sb.append("if (xdc.om.$$phase >= 5) xdc.om['ti.sysbios.family.arm.v7r.rti.Timer'].__initObject(__inst);\n");
                sb.append("__inst.$$bind('$$phase', xdc.om.$$phase);\n");
                sb.append("return null;\n");
            sb.append("}\n");
            Global.eval(sb.toString());
        }//isCFG
    }

    void Timer$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Timer$$SIZES()
    {
        Proto.Str so;
        Object fxn;

        so = (Proto.Str)om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.DeviceRegs", "ti.sysbios.family.arm.v7r.rti");
        sizes.clear();
        sizes.add(Global.newArray("RTIGCTRL", "UInt32"));
        sizes.add(Global.newArray("RTITBCTRL", "UInt32"));
        sizes.add(Global.newArray("RTICAPCTRL", "UInt32"));
        sizes.add(Global.newArray("RTICOMPCTRL", "UInt32"));
        sizes.add(Global.newArray("RTIFRC0", "UInt32"));
        sizes.add(Global.newArray("RTIUC0", "UInt32"));
        sizes.add(Global.newArray("RTICPUC0", "UInt32"));
        sizes.add(Global.newArray("RESERVED0", "UInt32"));
        sizes.add(Global.newArray("RTICAFRC0", "UInt32"));
        sizes.add(Global.newArray("RTICAUC0", "UInt32"));
        sizes.add(Global.newArray("RESERVED1", "UInt32"));
        sizes.add(Global.newArray("RESERVED2", "UInt32"));
        sizes.add(Global.newArray("RTIFRC1", "UInt32"));
        sizes.add(Global.newArray("RTIUC1", "UInt32"));
        sizes.add(Global.newArray("RTICPUC1", "UInt32"));
        sizes.add(Global.newArray("RESERVED3", "UInt32"));
        sizes.add(Global.newArray("RTICAFRC1", "UInt32"));
        sizes.add(Global.newArray("RTICAUC1", "UInt32"));
        sizes.add(Global.newArray("RESERVED4", "UInt32"));
        sizes.add(Global.newArray("RESERVED5", "UInt32"));
        sizes.add(Global.newArray("RTICOMP0", "UInt32"));
        sizes.add(Global.newArray("RTIUDCP0", "UInt32"));
        sizes.add(Global.newArray("RTICOMP1", "UInt32"));
        sizes.add(Global.newArray("RTIUDCP1", "UInt32"));
        sizes.add(Global.newArray("RTICOMP2", "UInt32"));
        sizes.add(Global.newArray("RTIUDCP2", "UInt32"));
        sizes.add(Global.newArray("RTICOMP3", "UInt32"));
        sizes.add(Global.newArray("RTIUDCP3", "UInt32"));
        sizes.add(Global.newArray("RTITBLCOMP", "UInt32"));
        sizes.add(Global.newArray("RTITBLHCOMP", "UInt32"));
        sizes.add(Global.newArray("RESERVED6", "UInt32"));
        sizes.add(Global.newArray("RESERVED7", "UInt32"));
        sizes.add(Global.newArray("RTISETINTENA", "UInt32"));
        sizes.add(Global.newArray("RTICLEARINTENA", "UInt32"));
        sizes.add(Global.newArray("RTIINTFLAG", "UInt32"));
        sizes.add(Global.newArray("RESERVED8", "UInt32"));
        sizes.add(Global.newArray("RTIDWDCTRL", "UInt32"));
        sizes.add(Global.newArray("RTIDWDPRLD", "UInt32"));
        sizes.add(Global.newArray("RTIWDSTATUS", "UInt32"));
        sizes.add(Global.newArray("RTIWDKEY", "UInt32"));
        sizes.add(Global.newArray("RTIDWDCNTR", "UInt32"));
        sizes.add(Global.newArray("RTIWWDRXNCTRL", "UInt32"));
        sizes.add(Global.newArray("RTIWWDSIZECTRL", "UInt32"));
        sizes.add(Global.newArray("RTIINTCLRENABLE", "UInt32"));
        sizes.add(Global.newArray("RTICOMP0CLR", "UInt32"));
        sizes.add(Global.newArray("RTICOMP1CLR", "UInt32"));
        sizes.add(Global.newArray("RTICOMP2CLR", "UInt32"));
        sizes.add(Global.newArray("RTICOMP3CLR", "UInt32"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sysbios.family.arm.v7r.rti.Timer.DeviceRegs']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sysbios.family.arm.v7r.rti.Timer.DeviceRegs']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sysbios.family.arm.v7r.rti.Timer.DeviceRegs'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.Instance_State", "ti.sysbios.family.arm.v7r.rti");
        sizes.clear();
        sizes.add(Global.newArray("__fxns", "UPtr"));
        sizes.add(Global.newArray("staticInst", "UShort"));
        sizes.add(Global.newArray("id", "TInt"));
        sizes.add(Global.newArray("runMode", "Nti.sysbios.interfaces.ITimer.RunMode;;;;"));
        sizes.add(Global.newArray("startMode", "Nti.sysbios.interfaces.ITimer.StartMode;;;"));
        sizes.add(Global.newArray("prescale", "UInt"));
        sizes.add(Global.newArray("period", "UInt"));
        sizes.add(Global.newArray("periodType", "Nti.sysbios.interfaces.ITimer.PeriodType;;;"));
        sizes.add(Global.newArray("intNum", "UInt"));
        sizes.add(Global.newArray("arg", "UIArg"));
        sizes.add(Global.newArray("tickFxn", "UFxn"));
        sizes.add(Global.newArray("extFreq", "Sxdc.runtime.Types;FreqHz"));
        sizes.add(Global.newArray("hwi", "UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sysbios.family.arm.v7r.rti.Timer.Instance_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sysbios.family.arm.v7r.rti.Timer.Instance_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sysbios.family.arm.v7r.rti.Timer.Instance_State'], fld); }");
        so.bind("$offsetof", fxn);
        so = (Proto.Str)om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.Module_State", "ti.sysbios.family.arm.v7r.rti");
        sizes.clear();
        sizes.add(Global.newArray("availMask", "UInt"));
        sizes.add(Global.newArray("handles", "A2;UPtr"));
        so.bind("$$sizes", Global.newArray(sizes.toArray()));
        fxn = Global.eval("function() { return $$sizeof(xdc.om['ti.sysbios.family.arm.v7r.rti.Timer.Module_State']); }");
        so.bind("$sizeof", fxn);
        fxn = Global.eval("function() { return $$alignof(xdc.om['ti.sysbios.family.arm.v7r.rti.Timer.Module_State']); }");
        so.bind("$alignof", fxn);
        fxn = Global.eval("function(fld) { return $$offsetof(xdc.om['ti.sysbios.family.arm.v7r.rti.Timer.Module_State'], fld); }");
        so.bind("$offsetof", fxn);
    }

    void Timer$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sysbios/family/arm/v7r/rti/Timer.xs");
        om.bind("ti.sysbios.family.arm.v7r.rti.Timer$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.Module", "ti.sysbios.family.arm.v7r.rti");
        po.init("ti.sysbios.family.arm.v7r.rti.Timer.Module", om.findStrict("ti.sysbios.interfaces.ITimer.Module", "ti.sysbios.family.arm.v7r.rti"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("ANY", Proto.Elm.newCNum("(xdc_UInt)"), Global.eval("~0"), "rh");
                po.addFld("MAX_PERIOD", Proto.Elm.newCNum("(xdc_UInt)"), 0xffffffffL, "rh");
                po.addFld("NUM_TIMER_DEVICES", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
                po.addFld("MIN_SWEEP_PERIOD", Proto.Elm.newCNum("(xdc_Int)"), 8L, "rh");
        if (isCFG) {
            po.addFld("rovViewInfo", (Proto)om.findStrict("xdc.rov.ViewInfo.Instance", "ti.sysbios.family.arm.v7r.rti"), $$UNDEF, "wh");
            po.addFld("A_invalidTimer", (Proto)om.findStrict("xdc.runtime.Assert$$Id", "ti.sysbios.family.arm.v7r.rti"), Global.newObject("msg", "A_invalidTimer: Invalid Timer Id."), "w");
            po.addFld("E_invalidTimer", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sysbios.family.arm.v7r.rti"), Global.newObject("msg", "E_invalidTimer: Invalid Timer Id %d"), "w");
            po.addFld("E_notAvailable", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sysbios.family.arm.v7r.rti"), Global.newObject("msg", "E_notAvailable: Timer not available %d"), "w");
            po.addFld("E_invalidHwiMask", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sysbios.family.arm.v7r.rti"), Global.newObject("msg", "E_InvalidMask: Mask in hwiParams cannot enable self"), "w");
            po.addFld("E_cannotSupport", (Proto)om.findStrict("xdc.runtime.Error$$Id", "ti.sysbios.family.arm.v7r.rti"), Global.newObject("msg", "E_cannotSupport: Timer cannot support requested period %d"), "w");
            po.addFld("rtiBaseAddress", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "wh");
            po.addFld("anyMask", Proto.Elm.newCNum("(xdc_UInt)"), 0x3L, "w");
            po.addFld("continueOnSuspend", $$T_Bool, false, "w");
            po.addFld("intFreq", (Proto)om.findStrict("xdc.runtime.Types.FreqHz", "ti.sysbios.family.arm.v7r.rti"), Global.newObject("lo", 0L, "hi", 0L), "w");
            po.addFld("startupNeeded", Proto.Elm.newCNum("(xdc_UInt)"), false, "w");
            po.addFld("intNumDef", new Proto.Arr(Proto.Elm.newCNum("(xdc_UInt8)"), false, xdc.services.intern.xsr.Enum.intValue(2L)), $$DEFAULT, "w");
        }//isCFG
        if (isCFG) {
                        po.addFxn("create", (Proto.Fxn)om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer$$create", "ti.sysbios.family.arm.v7r.rti"), Global.get("ti$sysbios$family$arm$v7r$rti$Timer$$create"));
                        po.addFxn("construct", (Proto.Fxn)om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer$$construct", "ti.sysbios.family.arm.v7r.rti"), Global.get("ti$sysbios$family$arm$v7r$rti$Timer$$construct"));
        }//isCFG
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v7r.rti.Timer$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v7r.rti.Timer$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v7r.rti.Timer$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$static$init");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v7r.rti.Timer$$module$static$init", true);
        if (fxn != null) po.addFxn("module$static$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v7r.rti.Timer$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$static$init");
        if (fxn != null) om.bind("ti.sysbios.family.arm.v7r.rti.Timer$$instance$static$init", true);
        if (fxn != null) po.addFxn("instance$static$init", $$T_Met, fxn);
                fxn = Global.get(cap, "getFreqMeta");
                if (fxn != null) po.addFxn("getFreqMeta", (Proto.Fxn)om.findStrict("ti.sysbios.interfaces.ITimer$$getFreqMeta", "ti.sysbios.family.arm.v7r.rti"), fxn);
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.Instance", "ti.sysbios.family.arm.v7r.rti");
        po.init("ti.sysbios.family.arm.v7r.rti.Timer.Instance", om.findStrict("ti.sysbios.interfaces.ITimer.Instance", "ti.sysbios.family.arm.v7r.rti"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("ANY", Proto.Elm.newCNum("(xdc_UInt)"), Global.eval("~0"), "rh");
                po.addFld("MAX_PERIOD", Proto.Elm.newCNum("(xdc_UInt)"), 0xffffffffL, "rh");
                po.addFld("NUM_TIMER_DEVICES", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
                po.addFld("MIN_SWEEP_PERIOD", Proto.Elm.newCNum("(xdc_Int)"), 8L, "rh");
        if (isCFG) {
            po.addFld("hwiParams", new Proto.Adr("ti_sysbios_family_arm_v7r_vim_Hwi_Params*", "PS"), null, "w");
            po.addFld("intNum", Proto.Elm.newCNum("(xdc_Int)"), Global.eval("-1"), "w");
            po.addFld("prescale", Proto.Elm.newCNum("(xdc_UInt8)"), 1L, "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sysbios.family.arm.v7r.rti"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer$$Params", "ti.sysbios.family.arm.v7r.rti");
        po.init("ti.sysbios.family.arm.v7r.rti.Timer.Params", om.findStrict("ti.sysbios.interfaces.ITimer$$Params", "ti.sysbios.family.arm.v7r.rti"));
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("ANY", Proto.Elm.newCNum("(xdc_UInt)"), Global.eval("~0"), "rh");
                po.addFld("MAX_PERIOD", Proto.Elm.newCNum("(xdc_UInt)"), 0xffffffffL, "rh");
                po.addFld("NUM_TIMER_DEVICES", Proto.Elm.newCNum("(xdc_Int)"), 2L, "rh");
                po.addFld("MIN_SWEEP_PERIOD", Proto.Elm.newCNum("(xdc_Int)"), 8L, "rh");
        if (isCFG) {
            po.addFld("hwiParams", new Proto.Adr("ti_sysbios_family_arm_v7r_vim_Hwi_Params*", "PS"), null, "w");
            po.addFld("intNum", Proto.Elm.newCNum("(xdc_Int)"), Global.eval("-1"), "w");
            po.addFld("prescale", Proto.Elm.newCNum("(xdc_UInt8)"), 1L, "w");
                        po.addFld("instance", (Proto)om.findStrict("xdc.runtime.IInstance.Params", "ti.sysbios.family.arm.v7r.rti"), $$UNDEF, "w");
        }//isCFG
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer$$Object", "ti.sysbios.family.arm.v7r.rti");
        po.init("ti.sysbios.family.arm.v7r.rti.Timer.Object", om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.Instance", "ti.sysbios.family.arm.v7r.rti"));
        // struct Timer.BasicView
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer$$BasicView", "ti.sysbios.family.arm.v7r.rti");
        po.init("ti.sysbios.family.arm.v7r.rti.Timer.BasicView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("halTimerHandle", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
                po.addFld("label", $$T_Str, $$UNDEF, "w");
                po.addFld("id", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("startMode", $$T_Str, $$UNDEF, "w");
                po.addFld("runMode", $$T_Str, $$UNDEF, "w");
                po.addFld("period", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("periodType", $$T_Str, $$UNDEF, "w");
                po.addFld("intNum", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("tickFxn", new Proto.Arr($$T_Str, false), $$DEFAULT, "w");
                po.addFld("arg", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
                po.addFld("extFreq", $$T_Str, $$UNDEF, "w");
                po.addFld("hwiHandle", $$T_Str, $$UNDEF, "w");
                po.addFxn("$xml", $$T_Met, Global.get("$$xml"));
        // struct Timer.DeviceView
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer$$DeviceView", "ti.sysbios.family.arm.v7r.rti");
        po.init("ti.sysbios.family.arm.v7r.rti.Timer.DeviceView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("id", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("device", $$T_Str, $$UNDEF, "w");
                po.addFld("devAddr", $$T_Str, $$UNDEF, "w");
                po.addFld("intNum", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("runMode", $$T_Str, $$UNDEF, "w");
                po.addFld("period", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("currCount", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("remainingCount", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("state", $$T_Str, $$UNDEF, "w");
        // struct Timer.ModuleView
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer$$ModuleView", "ti.sysbios.family.arm.v7r.rti");
        po.init("ti.sysbios.family.arm.v7r.rti.Timer.ModuleView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("availMask", $$T_Str, $$UNDEF, "w");
        // struct Timer.DeviceRegs
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer$$DeviceRegs", "ti.sysbios.family.arm.v7r.rti");
        po.init("ti.sysbios.family.arm.v7r.rti.Timer.DeviceRegs", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("RTIGCTRL", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RTITBCTRL", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RTICAPCTRL", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RTICOMPCTRL", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RTIFRC0", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RTIUC0", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RTICPUC0", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RESERVED0", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RTICAFRC0", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RTICAUC0", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RESERVED1", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RESERVED2", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RTIFRC1", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RTIUC1", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RTICPUC1", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RESERVED3", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RTICAFRC1", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RTICAUC1", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RESERVED4", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RESERVED5", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RTICOMP0", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RTIUDCP0", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RTICOMP1", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RTIUDCP1", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RTICOMP2", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RTIUDCP2", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RTICOMP3", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RTIUDCP3", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RTITBLCOMP", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RTITBLHCOMP", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RESERVED6", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RESERVED7", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RTISETINTENA", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RTICLEARINTENA", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RTIINTFLAG", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RESERVED8", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RTIDWDCTRL", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RTIDWDPRLD", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RTIWDSTATUS", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RTIWDKEY", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RTIDWDCNTR", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RTIWWDRXNCTRL", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RTIWWDSIZECTRL", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RTIINTCLRENABLE", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RTICOMP0CLR", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RTICOMP1CLR", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RTICOMP2CLR", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
                po.addFld("RTICOMP3CLR", Proto.Elm.newCNum("(xdc_UInt32)"), $$UNDEF, "w");
        // struct Timer.Instance_State
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer$$Instance_State", "ti.sysbios.family.arm.v7r.rti");
        po.init("ti.sysbios.family.arm.v7r.rti.Timer.Instance_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("staticInst", $$T_Bool, $$UNDEF, "w");
                po.addFld("id", Proto.Elm.newCNum("(xdc_Int)"), $$UNDEF, "w");
                po.addFld("runMode", (Proto)om.findStrict("ti.sysbios.interfaces.ITimer.RunMode", "ti.sysbios.family.arm.v7r.rti"), $$UNDEF, "w");
                po.addFld("startMode", (Proto)om.findStrict("ti.sysbios.interfaces.ITimer.StartMode", "ti.sysbios.family.arm.v7r.rti"), $$UNDEF, "w");
                po.addFld("prescale", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("period", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("periodType", (Proto)om.findStrict("ti.sysbios.interfaces.ITimer.PeriodType", "ti.sysbios.family.arm.v7r.rti"), $$UNDEF, "w");
                po.addFld("intNum", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("arg", new Proto.Adr("xdc_UArg", "Pv"), $$UNDEF, "w");
                po.addFld("tickFxn", new Proto.Adr("xdc_Void(*)(xdc_UArg)", "PFv"), $$UNDEF, "w");
                po.addFld("extFreq", (Proto)om.findStrict("xdc.runtime.Types.FreqHz", "ti.sysbios.family.arm.v7r.rti"), $$DEFAULT, "w");
                po.addFld("hwi", (Proto)om.findStrict("ti.sysbios.family.arm.v7r.vim.Hwi.Handle", "ti.sysbios.family.arm.v7r.rti"), $$UNDEF, "w");
        // struct Timer.Module_State
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer$$Module_State", "ti.sysbios.family.arm.v7r.rti");
        po.init("ti.sysbios.family.arm.v7r.rti.Timer.Module_State", null);
                po.addFld("$hostonly", $$T_Num, 0, "r");
                po.addFld("availMask", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "w");
                po.addFld("handles", new Proto.Arr((Proto)om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.Handle", "ti.sysbios.family.arm.v7r.rti"), false, xdc.services.intern.xsr.Enum.intValue(2L)), $$DEFAULT, "w");
    }

    void Timer$$ROV()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer", "ti.sysbios.family.arm.v7r.rti");
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer$$Instance_State", "ti.sysbios.family.arm.v7r.rti");
        po.addFld("__fxns", new Proto.Adr("xdc_Ptr", "Pv"), $$UNDEF, "w");
        vo.bind("DeviceRegs$fetchDesc", Global.newObject("type", "ti.sysbios.family.arm.v7r.rti.Timer.DeviceRegs", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer$$DeviceRegs", "ti.sysbios.family.arm.v7r.rti");
        vo.bind("Instance_State$fetchDesc", Global.newObject("type", "ti.sysbios.family.arm.v7r.rti.Timer.Instance_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer$$Instance_State", "ti.sysbios.family.arm.v7r.rti");
        vo.bind("Module_State$fetchDesc", Global.newObject("type", "ti.sysbios.family.arm.v7r.rti.Timer.Module_State", "isScalar", false));
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer$$Module_State", "ti.sysbios.family.arm.v7r.rti");
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.sysbios.family.arm.v7r.rti.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.sysbios.family.arm.v7r.rti"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/sysbios/family/arm/v7r/rti/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.sysbios.family.arm.v7r.rti"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.sysbios.family.arm.v7r.rti"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.sysbios.family.arm.v7r.rti"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.sysbios.family.arm.v7r.rti"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.sysbios.family.arm.v7r.rti"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.sysbios.family.arm.v7r.rti"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.sysbios.family.arm.v7r.rti", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.sysbios.family.arm.v7r.rti");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.sysbios.family.arm.v7r.rti.");
        pkgV.bind("$vers", Global.newArray(2, 0, 0, 0));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        imports.add(Global.newArray("ti.sysbios.interfaces", Global.newArray()));
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.sysbios.family.arm.v7r.rti'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("if ('ti.sysbios.family.arm.v7r.rti$$stat$base' in xdc.om) {\n");
            sb.append("pkg.packageBase = xdc.om['ti.sysbios.family.arm.v7r.rti$$stat$base'];\n");
            sb.append("pkg.packageRepository = xdc.om['ti.sysbios.family.arm.v7r.rti$$stat$root'];\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/sysbios/debug/ti.sysbios.family.arm.v7r.rti.aer5f',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/sysbios/debug/ti.sysbios.family.arm.v7r.rti.aer5f', {target: 'ti.targets.arm.elf.R5F', suffix: 'er5f'}],\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void Timer$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer", "ti.sysbios.family.arm.v7r.rti");
        po = (Proto.Obj)om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.Module", "ti.sysbios.family.arm.v7r.rti");
        vo.init2(po, "ti.sysbios.family.arm.v7r.rti.Timer", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer$$capsule", "ti.sysbios.family.arm.v7r.rti"));
        vo.bind("Instance", om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.Instance", "ti.sysbios.family.arm.v7r.rti"));
        vo.bind("Params", om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.Params", "ti.sysbios.family.arm.v7r.rti"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.Params", "ti.sysbios.family.arm.v7r.rti")).newInstance());
        vo.bind("Handle", om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.Handle", "ti.sysbios.family.arm.v7r.rti"));
        vo.bind("$package", om.findStrict("ti.sysbios.family.arm.v7r.rti", "ti.sysbios.family.arm.v7r.rti"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        mcfgs.add("Module__diagsEnabled");
        icfgs.add("Module__diagsEnabled");
        mcfgs.add("Module__diagsIncluded");
        icfgs.add("Module__diagsIncluded");
        mcfgs.add("Module__diagsMask");
        icfgs.add("Module__diagsMask");
        mcfgs.add("Module__gateObj");
        icfgs.add("Module__gateObj");
        mcfgs.add("Module__gatePrms");
        icfgs.add("Module__gatePrms");
        mcfgs.add("Module__id");
        icfgs.add("Module__id");
        mcfgs.add("Module__loggerDefined");
        icfgs.add("Module__loggerDefined");
        mcfgs.add("Module__loggerObj");
        icfgs.add("Module__loggerObj");
        mcfgs.add("Module__loggerFxn0");
        icfgs.add("Module__loggerFxn0");
        mcfgs.add("Module__loggerFxn1");
        icfgs.add("Module__loggerFxn1");
        mcfgs.add("Module__loggerFxn2");
        icfgs.add("Module__loggerFxn2");
        mcfgs.add("Module__loggerFxn4");
        icfgs.add("Module__loggerFxn4");
        mcfgs.add("Module__loggerFxn8");
        icfgs.add("Module__loggerFxn8");
        mcfgs.add("Module__startupDoneFxn");
        icfgs.add("Module__startupDoneFxn");
        mcfgs.add("Object__count");
        icfgs.add("Object__count");
        mcfgs.add("Object__heap");
        icfgs.add("Object__heap");
        mcfgs.add("Object__sizeof");
        icfgs.add("Object__sizeof");
        mcfgs.add("Object__table");
        icfgs.add("Object__table");
        vo.bind("FuncPtr", om.findStrict("ti.sysbios.interfaces.ITimer.FuncPtr", "ti.sysbios.family.arm.v7r.rti"));
        vo.bind("StartMode", om.findStrict("ti.sysbios.interfaces.ITimer.StartMode", "ti.sysbios.family.arm.v7r.rti"));
        vo.bind("RunMode", om.findStrict("ti.sysbios.interfaces.ITimer.RunMode", "ti.sysbios.family.arm.v7r.rti"));
        vo.bind("Status", om.findStrict("ti.sysbios.interfaces.ITimer.Status", "ti.sysbios.family.arm.v7r.rti"));
        vo.bind("PeriodType", om.findStrict("ti.sysbios.interfaces.ITimer.PeriodType", "ti.sysbios.family.arm.v7r.rti"));
        vo.bind("BasicView", om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.BasicView", "ti.sysbios.family.arm.v7r.rti"));
        tdefs.add(om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.BasicView", "ti.sysbios.family.arm.v7r.rti"));
        vo.bind("DeviceView", om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.DeviceView", "ti.sysbios.family.arm.v7r.rti"));
        tdefs.add(om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.DeviceView", "ti.sysbios.family.arm.v7r.rti"));
        vo.bind("ModuleView", om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.ModuleView", "ti.sysbios.family.arm.v7r.rti"));
        tdefs.add(om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.ModuleView", "ti.sysbios.family.arm.v7r.rti"));
        mcfgs.add("A_invalidTimer");
        mcfgs.add("E_invalidTimer");
        mcfgs.add("E_notAvailable");
        mcfgs.add("E_invalidHwiMask");
        mcfgs.add("E_cannotSupport");
        mcfgs.add("anyMask");
        mcfgs.add("continueOnSuspend");
        mcfgs.add("intFreq");
        vo.bind("DeviceRegs", om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.DeviceRegs", "ti.sysbios.family.arm.v7r.rti"));
        tdefs.add(om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.DeviceRegs", "ti.sysbios.family.arm.v7r.rti"));
        vo.bind("deviceRegs", om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.deviceRegs", "ti.sysbios.family.arm.v7r.rti"));
        mcfgs.add("startupNeeded");
        icfgs.add("startupNeeded");
        mcfgs.add("intNumDef");
        icfgs.add("intNumDef");
        vo.bind("Instance_State", om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.Instance_State", "ti.sysbios.family.arm.v7r.rti"));
        tdefs.add(om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.Instance_State", "ti.sysbios.family.arm.v7r.rti"));
        vo.bind("Module_State", om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.Module_State", "ti.sysbios.family.arm.v7r.rti"));
        tdefs.add(om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.Module_State", "ti.sysbios.family.arm.v7r.rti"));
        vo.bind("StartMode_AUTO", om.findStrict("ti.sysbios.interfaces.ITimer.StartMode_AUTO", "ti.sysbios.family.arm.v7r.rti"));
        vo.bind("StartMode_USER", om.findStrict("ti.sysbios.interfaces.ITimer.StartMode_USER", "ti.sysbios.family.arm.v7r.rti"));
        vo.bind("RunMode_CONTINUOUS", om.findStrict("ti.sysbios.interfaces.ITimer.RunMode_CONTINUOUS", "ti.sysbios.family.arm.v7r.rti"));
        vo.bind("RunMode_ONESHOT", om.findStrict("ti.sysbios.interfaces.ITimer.RunMode_ONESHOT", "ti.sysbios.family.arm.v7r.rti"));
        vo.bind("RunMode_DYNAMIC", om.findStrict("ti.sysbios.interfaces.ITimer.RunMode_DYNAMIC", "ti.sysbios.family.arm.v7r.rti"));
        vo.bind("Status_INUSE", om.findStrict("ti.sysbios.interfaces.ITimer.Status_INUSE", "ti.sysbios.family.arm.v7r.rti"));
        vo.bind("Status_FREE", om.findStrict("ti.sysbios.interfaces.ITimer.Status_FREE", "ti.sysbios.family.arm.v7r.rti"));
        vo.bind("PeriodType_MICROSECS", om.findStrict("ti.sysbios.interfaces.ITimer.PeriodType_MICROSECS", "ti.sysbios.family.arm.v7r.rti"));
        vo.bind("PeriodType_COUNTS", om.findStrict("ti.sysbios.interfaces.ITimer.PeriodType_COUNTS", "ti.sysbios.family.arm.v7r.rti"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("ti.sysbios.interfaces");
        inherits.add("xdc.runtime");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.sysbios.family.arm.v7r.rti")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        if (isCFG) {
            Proto.Str ps = (Proto.Str)vo.find("Module_State");
            if (ps != null) vo.bind("$object", ps.newInstance());
            vo.bind("$$meta_iobj", om.has("ti.sysbios.family.arm.v7r.rti.Timer$$instance$static$init", null) ? 1 : 0);
            vo.bind("__initObject", Global.get("ti$sysbios$family$arm$v7r$rti$Timer$$__initObject"));
        }//isCFG
        vo.bind("getNumTimers", om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.getNumTimers", "ti.sysbios.family.arm.v7r.rti"));
        vo.bind("getStatus", om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.getStatus", "ti.sysbios.family.arm.v7r.rti"));
        vo.bind("startup", om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.startup", "ti.sysbios.family.arm.v7r.rti"));
        vo.bind("oneShotStub", om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.oneShotStub", "ti.sysbios.family.arm.v7r.rti"));
        vo.bind("periodicStub", om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.periodicStub", "ti.sysbios.family.arm.v7r.rti"));
        vo.bind("getHandle", om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.getHandle", "ti.sysbios.family.arm.v7r.rti"));
        vo.bind("initDevice", om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.initDevice", "ti.sysbios.family.arm.v7r.rti"));
        vo.bind("postInit", om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.postInit", "ti.sysbios.family.arm.v7r.rti"));
        vo.bind("checkOverflow", om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.checkOverflow", "ti.sysbios.family.arm.v7r.rti"));
        vo.bind("$$fxntab", Global.newArray("ti_sysbios_family_arm_v7r_rti_Timer_Handle__label__E", "ti_sysbios_family_arm_v7r_rti_Timer_Module__startupDone__E", "ti_sysbios_family_arm_v7r_rti_Timer_Object__create__E", "ti_sysbios_family_arm_v7r_rti_Timer_Object__delete__E", "ti_sysbios_family_arm_v7r_rti_Timer_Object__destruct__E", "ti_sysbios_family_arm_v7r_rti_Timer_Object__get__E", "ti_sysbios_family_arm_v7r_rti_Timer_Object__first__E", "ti_sysbios_family_arm_v7r_rti_Timer_Object__next__E", "ti_sysbios_family_arm_v7r_rti_Timer_Params__init__E", "ti_sysbios_family_arm_v7r_rti_Timer_getNumTimers__E", "ti_sysbios_family_arm_v7r_rti_Timer_getStatus__E", "ti_sysbios_family_arm_v7r_rti_Timer_startup__E", "ti_sysbios_family_arm_v7r_rti_Timer_getMaxTicks__E", "ti_sysbios_family_arm_v7r_rti_Timer_setNextTick__E", "ti_sysbios_family_arm_v7r_rti_Timer_start__E", "ti_sysbios_family_arm_v7r_rti_Timer_stop__E", "ti_sysbios_family_arm_v7r_rti_Timer_setPeriod__E", "ti_sysbios_family_arm_v7r_rti_Timer_setPeriodMicroSecs__E", "ti_sysbios_family_arm_v7r_rti_Timer_getPeriod__E", "ti_sysbios_family_arm_v7r_rti_Timer_getCount__E", "ti_sysbios_family_arm_v7r_rti_Timer_getFreq__E", "ti_sysbios_family_arm_v7r_rti_Timer_getFunc__E", "ti_sysbios_family_arm_v7r_rti_Timer_setFunc__E", "ti_sysbios_family_arm_v7r_rti_Timer_trigger__E", "ti_sysbios_family_arm_v7r_rti_Timer_getExpiredCounts__E", "ti_sysbios_family_arm_v7r_rti_Timer_getExpiredTicks__E", "ti_sysbios_family_arm_v7r_rti_Timer_getCurrentTick__E", "ti_sysbios_family_arm_v7r_rti_Timer_oneShotStub__E", "ti_sysbios_family_arm_v7r_rti_Timer_periodicStub__E", "ti_sysbios_family_arm_v7r_rti_Timer_getHandle__E", "ti_sysbios_family_arm_v7r_rti_Timer_reconfig__E", "ti_sysbios_family_arm_v7r_rti_Timer_ackInterrupt__E"));
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray("E_invalidTimer", "E_notAvailable", "E_invalidHwiMask", "E_cannotSupport"));
        vo.bind("$$assertDescCfgs", Global.newArray("A_invalidTimer"));
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.setElem("", true);
        atmap.seal("length");
        vo.bind("Object", om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer.Object", "ti.sysbios.family.arm.v7r.rti"));
        vo.bind("MODULE_STARTUP$", 1);
        vo.bind("PROXY$", 0);
        loggables.clear();
        vo.bind("$$loggables", loggables.toArray());
        pkgV.bind("Timer", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Timer");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
            Object srcP = ((XScriptO)om.findStrict("xdc.runtime.IInstance", "ti.sysbios.family.arm.v7r.rti")).findStrict("PARAMS", "ti.sysbios.family.arm.v7r.rti");
            Scriptable dstP;

            dstP = (Scriptable)((XScriptO)om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer", "ti.sysbios.family.arm.v7r.rti")).findStrict("PARAMS", "ti.sysbios.family.arm.v7r.rti");
            Global.put(dstP, "instance", srcP);
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer", "ti.sysbios.family.arm.v7r.rti"));
        if (isCFG) {
            vo = (Value.Obj)om.findStrict("ti.sysbios.family.arm.v7r.rti.Timer", "ti.sysbios.family.arm.v7r.rti");
            Global.put(vo, "rovViewInfo", Global.callFxn("create", (Scriptable)om.find("xdc.rov.ViewInfo"), Global.newObject("viewMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"Basic", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE"), "viewInitFxn", "viewInitBasic", "structName", "BasicView")}), Global.newArray(new Object[]{"Device", Global.newObject("type", om.find("xdc.rov.ViewInfo.INSTANCE"), "viewInitFxn", "viewInitDevice", "structName", "DeviceView")}), Global.newArray(new Object[]{"Module", Global.newObject("type", om.find("xdc.rov.ViewInfo.MODULE"), "viewInitFxn", "viewInitModule", "structName", "ModuleView")})}))));
        }//isCFG
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.sysbios.family.arm.v7r.rti.Timer")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.sysbios.family.arm.v7r.rti")).add(pkgV);
    }

    public void exec( Scriptable xdcO, Session ses )
    {
        this.xdcO = xdcO;
        this.ses = ses;
        om = (Value.Obj)xdcO.get("om", null);

        Object o = om.geto("$name");
        String s = o instanceof String ? (String)o : null;
        isCFG = s != null && s.equals("cfg");
        isROV = s != null && s.equals("rov");

        $$IMPORTS();
        $$OBJECTS();
        Timer$$OBJECTS();
        Timer$$CONSTS();
        Timer$$CREATES();
        Timer$$FUNCTIONS();
        Timer$$SIZES();
        Timer$$TYPES();
        if (isROV) {
            Timer$$ROV();
        }//isROV
        $$SINGLETONS();
        Timer$$SINGLETONS();
        $$INITIALIZATION();
    }
}
