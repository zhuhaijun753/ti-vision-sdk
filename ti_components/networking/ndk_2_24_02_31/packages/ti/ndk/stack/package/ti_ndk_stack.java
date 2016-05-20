/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-z63
 */
import java.util.*;
import org.mozilla.javascript.*;
import xdc.services.intern.xsr.*;
import xdc.services.spec.Session;

public class ti_ndk_stack
{
    static final String VERS = "@(#) xdc-z63\n";

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
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.ndk.stack.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.ndk.stack", new Value.Obj("ti.ndk.stack", pkgP));
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.ndk.stack.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.ndk.stack"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/ndk/stack/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.ndk.stack"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.ndk.stack"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.ndk.stack"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.ndk.stack"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.ndk.stack"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.ndk.stack"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.ndk.stack", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.ndk.stack");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.ndk.stack.");
        pkgV.bind("$vers", Global.newArray());
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.ndk.stack'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/stk.ae66',\n");
            sb.append("'lib/stk6.ae66',\n");
            sb.append("'lib/stk_ppp_pppoe.ae66',\n");
            sb.append("'lib/stk6_ppp_pppoe.ae66',\n");
            sb.append("'lib/stk_ppp.ae66',\n");
            sb.append("'lib/stk6_ppp.ae66',\n");
            sb.append("'lib/stk_nat.ae66',\n");
            sb.append("'lib/stk6_nat.ae66',\n");
            sb.append("'lib/stk_nat_ppp.ae66',\n");
            sb.append("'lib/stk6_nat_ppp.ae66',\n");
            sb.append("'lib/stk_nat_ppp_pppoe.ae66',\n");
            sb.append("'lib/stk6_nat_ppp_pppoe.ae66',\n");
            sb.append("'lib/stk.ae66e',\n");
            sb.append("'lib/stk6.ae66e',\n");
            sb.append("'lib/stk_ppp_pppoe.ae66e',\n");
            sb.append("'lib/stk6_ppp_pppoe.ae66e',\n");
            sb.append("'lib/stk_ppp.ae66e',\n");
            sb.append("'lib/stk6_ppp.ae66e',\n");
            sb.append("'lib/stk_nat.ae66e',\n");
            sb.append("'lib/stk6_nat.ae66e',\n");
            sb.append("'lib/stk_nat_ppp.ae66e',\n");
            sb.append("'lib/stk6_nat_ppp.ae66e',\n");
            sb.append("'lib/stk_nat_ppp_pppoe.ae66e',\n");
            sb.append("'lib/stk6_nat_ppp_pppoe.ae66e',\n");
            sb.append("'lib/stk.ae674',\n");
            sb.append("'lib/stk6.ae674',\n");
            sb.append("'lib/stk_ppp_pppoe.ae674',\n");
            sb.append("'lib/stk6_ppp_pppoe.ae674',\n");
            sb.append("'lib/stk_ppp.ae674',\n");
            sb.append("'lib/stk6_ppp.ae674',\n");
            sb.append("'lib/stk_nat.ae674',\n");
            sb.append("'lib/stk6_nat.ae674',\n");
            sb.append("'lib/stk_nat_ppp.ae674',\n");
            sb.append("'lib/stk6_nat_ppp.ae674',\n");
            sb.append("'lib/stk_nat_ppp_pppoe.ae674',\n");
            sb.append("'lib/stk6_nat_ppp_pppoe.ae674',\n");
            sb.append("'lib/stk.ae9',\n");
            sb.append("'lib/stk6.ae9',\n");
            sb.append("'lib/stk_ppp_pppoe.ae9',\n");
            sb.append("'lib/stk6_ppp_pppoe.ae9',\n");
            sb.append("'lib/stk_ppp.ae9',\n");
            sb.append("'lib/stk6_ppp.ae9',\n");
            sb.append("'lib/stk_nat.ae9',\n");
            sb.append("'lib/stk6_nat.ae9',\n");
            sb.append("'lib/stk_nat_ppp.ae9',\n");
            sb.append("'lib/stk6_nat_ppp.ae9',\n");
            sb.append("'lib/stk_nat_ppp_pppoe.ae9',\n");
            sb.append("'lib/stk6_nat_ppp_pppoe.ae9',\n");
            sb.append("'lib/stk.aea8f',\n");
            sb.append("'lib/stk6.aea8f',\n");
            sb.append("'lib/stk_ppp_pppoe.aea8f',\n");
            sb.append("'lib/stk6_ppp_pppoe.aea8f',\n");
            sb.append("'lib/stk_ppp.aea8f',\n");
            sb.append("'lib/stk6_ppp.aea8f',\n");
            sb.append("'lib/stk_nat.aea8f',\n");
            sb.append("'lib/stk6_nat.aea8f',\n");
            sb.append("'lib/stk_nat_ppp.aea8f',\n");
            sb.append("'lib/stk6_nat_ppp.aea8f',\n");
            sb.append("'lib/stk_nat_ppp_pppoe.aea8f',\n");
            sb.append("'lib/stk6_nat_ppp_pppoe.aea8f',\n");
            sb.append("'lib/stk.aea8fnv',\n");
            sb.append("'lib/stk6.aea8fnv',\n");
            sb.append("'lib/stk_ppp_pppoe.aea8fnv',\n");
            sb.append("'lib/stk6_ppp_pppoe.aea8fnv',\n");
            sb.append("'lib/stk_ppp.aea8fnv',\n");
            sb.append("'lib/stk6_ppp.aea8fnv',\n");
            sb.append("'lib/stk_nat.aea8fnv',\n");
            sb.append("'lib/stk6_nat.aea8fnv',\n");
            sb.append("'lib/stk_nat_ppp.aea8fnv',\n");
            sb.append("'lib/stk6_nat_ppp.aea8fnv',\n");
            sb.append("'lib/stk_nat_ppp_pppoe.aea8fnv',\n");
            sb.append("'lib/stk6_nat_ppp_pppoe.aea8fnv',\n");
            sb.append("'lib/stk.aem3',\n");
            sb.append("'lib/stk6.aem3',\n");
            sb.append("'lib/stk_ppp_pppoe.aem3',\n");
            sb.append("'lib/stk6_ppp_pppoe.aem3',\n");
            sb.append("'lib/stk_ppp.aem3',\n");
            sb.append("'lib/stk6_ppp.aem3',\n");
            sb.append("'lib/stk_nat.aem3',\n");
            sb.append("'lib/stk6_nat.aem3',\n");
            sb.append("'lib/stk_nat_ppp.aem3',\n");
            sb.append("'lib/stk6_nat_ppp.aem3',\n");
            sb.append("'lib/stk_nat_ppp_pppoe.aem3',\n");
            sb.append("'lib/stk6_nat_ppp_pppoe.aem3',\n");
            sb.append("'lib/stk.aem4',\n");
            sb.append("'lib/stk6.aem4',\n");
            sb.append("'lib/stk_ppp_pppoe.aem4',\n");
            sb.append("'lib/stk6_ppp_pppoe.aem4',\n");
            sb.append("'lib/stk_ppp.aem4',\n");
            sb.append("'lib/stk6_ppp.aem4',\n");
            sb.append("'lib/stk_nat.aem4',\n");
            sb.append("'lib/stk6_nat.aem4',\n");
            sb.append("'lib/stk_nat_ppp.aem4',\n");
            sb.append("'lib/stk6_nat_ppp.aem4',\n");
            sb.append("'lib/stk_nat_ppp_pppoe.aem4',\n");
            sb.append("'lib/stk6_nat_ppp_pppoe.aem4',\n");
            sb.append("'lib/stk.aem4f',\n");
            sb.append("'lib/stk6.aem4f',\n");
            sb.append("'lib/stk_ppp_pppoe.aem4f',\n");
            sb.append("'lib/stk6_ppp_pppoe.aem4f',\n");
            sb.append("'lib/stk_ppp.aem4f',\n");
            sb.append("'lib/stk6_ppp.aem4f',\n");
            sb.append("'lib/stk_nat.aem4f',\n");
            sb.append("'lib/stk6_nat.aem4f',\n");
            sb.append("'lib/stk_nat_ppp.aem4f',\n");
            sb.append("'lib/stk6_nat_ppp.aem4f',\n");
            sb.append("'lib/stk_nat_ppp_pppoe.aem4f',\n");
            sb.append("'lib/stk6_nat_ppp_pppoe.aem4f',\n");
            sb.append("'lib/stk.am3g',\n");
            sb.append("'lib/stk6.am3g',\n");
            sb.append("'lib/stk_ppp_pppoe.am3g',\n");
            sb.append("'lib/stk6_ppp_pppoe.am3g',\n");
            sb.append("'lib/stk_ppp.am3g',\n");
            sb.append("'lib/stk6_ppp.am3g',\n");
            sb.append("'lib/stk_nat.am3g',\n");
            sb.append("'lib/stk6_nat.am3g',\n");
            sb.append("'lib/stk_nat_ppp.am3g',\n");
            sb.append("'lib/stk6_nat_ppp.am3g',\n");
            sb.append("'lib/stk_nat_ppp_pppoe.am3g',\n");
            sb.append("'lib/stk6_nat_ppp_pppoe.am3g',\n");
            sb.append("'lib/stk.am4g',\n");
            sb.append("'lib/stk6.am4g',\n");
            sb.append("'lib/stk_ppp_pppoe.am4g',\n");
            sb.append("'lib/stk6_ppp_pppoe.am4g',\n");
            sb.append("'lib/stk_ppp.am4g',\n");
            sb.append("'lib/stk6_ppp.am4g',\n");
            sb.append("'lib/stk_nat.am4g',\n");
            sb.append("'lib/stk6_nat.am4g',\n");
            sb.append("'lib/stk_nat_ppp.am4g',\n");
            sb.append("'lib/stk6_nat_ppp.am4g',\n");
            sb.append("'lib/stk_nat_ppp_pppoe.am4g',\n");
            sb.append("'lib/stk6_nat_ppp_pppoe.am4g',\n");
            sb.append("'lib/stk.am4fg',\n");
            sb.append("'lib/stk6.am4fg',\n");
            sb.append("'lib/stk_ppp_pppoe.am4fg',\n");
            sb.append("'lib/stk6_ppp_pppoe.am4fg',\n");
            sb.append("'lib/stk_ppp.am4fg',\n");
            sb.append("'lib/stk6_ppp.am4fg',\n");
            sb.append("'lib/stk_nat.am4fg',\n");
            sb.append("'lib/stk6_nat.am4fg',\n");
            sb.append("'lib/stk_nat_ppp.am4fg',\n");
            sb.append("'lib/stk6_nat_ppp.am4fg',\n");
            sb.append("'lib/stk_nat_ppp_pppoe.am4fg',\n");
            sb.append("'lib/stk6_nat_ppp_pppoe.am4fg',\n");
            sb.append("'lib/stk.aa8fg',\n");
            sb.append("'lib/stk6.aa8fg',\n");
            sb.append("'lib/stk_ppp_pppoe.aa8fg',\n");
            sb.append("'lib/stk6_ppp_pppoe.aa8fg',\n");
            sb.append("'lib/stk_ppp.aa8fg',\n");
            sb.append("'lib/stk6_ppp.aa8fg',\n");
            sb.append("'lib/stk_nat.aa8fg',\n");
            sb.append("'lib/stk6_nat.aa8fg',\n");
            sb.append("'lib/stk_nat_ppp.aa8fg',\n");
            sb.append("'lib/stk6_nat_ppp.aa8fg',\n");
            sb.append("'lib/stk_nat_ppp_pppoe.aa8fg',\n");
            sb.append("'lib/stk6_nat_ppp_pppoe.aa8fg',\n");
            sb.append("'lib/stk.aa9fg',\n");
            sb.append("'lib/stk6.aa9fg',\n");
            sb.append("'lib/stk_ppp_pppoe.aa9fg',\n");
            sb.append("'lib/stk6_ppp_pppoe.aa9fg',\n");
            sb.append("'lib/stk_ppp.aa9fg',\n");
            sb.append("'lib/stk6_ppp.aa9fg',\n");
            sb.append("'lib/stk_nat.aa9fg',\n");
            sb.append("'lib/stk6_nat.aa9fg',\n");
            sb.append("'lib/stk_nat_ppp.aa9fg',\n");
            sb.append("'lib/stk6_nat_ppp.aa9fg',\n");
            sb.append("'lib/stk_nat_ppp_pppoe.aa9fg',\n");
            sb.append("'lib/stk6_nat_ppp_pppoe.aa9fg',\n");
            sb.append("'lib/stk.aa15fg',\n");
            sb.append("'lib/stk6.aa15fg',\n");
            sb.append("'lib/stk_ppp_pppoe.aa15fg',\n");
            sb.append("'lib/stk6_ppp_pppoe.aa15fg',\n");
            sb.append("'lib/stk_ppp.aa15fg',\n");
            sb.append("'lib/stk6_ppp.aa15fg',\n");
            sb.append("'lib/stk_nat.aa15fg',\n");
            sb.append("'lib/stk6_nat.aa15fg',\n");
            sb.append("'lib/stk_nat_ppp.aa15fg',\n");
            sb.append("'lib/stk6_nat_ppp.aa15fg',\n");
            sb.append("'lib/stk_nat_ppp_pppoe.aa15fg',\n");
            sb.append("'lib/stk6_nat_ppp_pppoe.aa15fg',\n");
            sb.append("'lib/stk.arm3',\n");
            sb.append("'lib/stk6.arm3',\n");
            sb.append("'lib/stk_ppp_pppoe.arm3',\n");
            sb.append("'lib/stk6_ppp_pppoe.arm3',\n");
            sb.append("'lib/stk_ppp.arm3',\n");
            sb.append("'lib/stk6_ppp.arm3',\n");
            sb.append("'lib/stk_nat.arm3',\n");
            sb.append("'lib/stk6_nat.arm3',\n");
            sb.append("'lib/stk_nat_ppp.arm3',\n");
            sb.append("'lib/stk6_nat_ppp.arm3',\n");
            sb.append("'lib/stk_nat_ppp_pppoe.arm3',\n");
            sb.append("'lib/stk6_nat_ppp_pppoe.arm3',\n");
            sb.append("'lib/stk.arm4',\n");
            sb.append("'lib/stk6.arm4',\n");
            sb.append("'lib/stk_ppp_pppoe.arm4',\n");
            sb.append("'lib/stk6_ppp_pppoe.arm4',\n");
            sb.append("'lib/stk_ppp.arm4',\n");
            sb.append("'lib/stk6_ppp.arm4',\n");
            sb.append("'lib/stk_nat.arm4',\n");
            sb.append("'lib/stk6_nat.arm4',\n");
            sb.append("'lib/stk_nat_ppp.arm4',\n");
            sb.append("'lib/stk6_nat_ppp.arm4',\n");
            sb.append("'lib/stk_nat_ppp_pppoe.arm4',\n");
            sb.append("'lib/stk6_nat_ppp_pppoe.arm4',\n");
            sb.append("'lib/stk.arm4f',\n");
            sb.append("'lib/stk6.arm4f',\n");
            sb.append("'lib/stk_ppp_pppoe.arm4f',\n");
            sb.append("'lib/stk6_ppp_pppoe.arm4f',\n");
            sb.append("'lib/stk_ppp.arm4f',\n");
            sb.append("'lib/stk6_ppp.arm4f',\n");
            sb.append("'lib/stk_nat.arm4f',\n");
            sb.append("'lib/stk6_nat.arm4f',\n");
            sb.append("'lib/stk_nat_ppp.arm4f',\n");
            sb.append("'lib/stk6_nat_ppp.arm4f',\n");
            sb.append("'lib/stk_nat_ppp_pppoe.arm4f',\n");
            sb.append("'lib/stk6_nat_ppp_pppoe.arm4f',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/stk.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/stk6.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/stk_ppp_pppoe.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/stk6_ppp_pppoe.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/stk_ppp.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/stk6_ppp.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/stk_nat.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/stk6_nat.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/stk_nat_ppp.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/stk6_nat_ppp.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/stk_nat_ppp_pppoe.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/stk6_nat_ppp_pppoe.ae66', {target: 'ti.targets.elf.C66', suffix: 'e66'}],\n");
            sb.append("['lib/stk.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/stk6.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/stk_ppp_pppoe.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/stk6_ppp_pppoe.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/stk_ppp.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/stk6_ppp.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/stk_nat.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/stk6_nat.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/stk_nat_ppp.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/stk6_nat_ppp.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/stk_nat_ppp_pppoe.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/stk6_nat_ppp_pppoe.ae66e', {target: 'ti.targets.elf.C66_big_endian', suffix: 'e66e'}],\n");
            sb.append("['lib/stk.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/stk6.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/stk_ppp_pppoe.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/stk6_ppp_pppoe.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/stk_ppp.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/stk6_ppp.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/stk_nat.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/stk6_nat.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/stk_nat_ppp.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/stk6_nat_ppp.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/stk_nat_ppp_pppoe.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/stk6_nat_ppp_pppoe.ae674', {target: 'ti.targets.elf.C674', suffix: 'e674'}],\n");
            sb.append("['lib/stk.ae9', {target: 'ti.targets.arm.elf.Arm9', suffix: 'e9'}],\n");
            sb.append("['lib/stk6.ae9', {target: 'ti.targets.arm.elf.Arm9', suffix: 'e9'}],\n");
            sb.append("['lib/stk_ppp_pppoe.ae9', {target: 'ti.targets.arm.elf.Arm9', suffix: 'e9'}],\n");
            sb.append("['lib/stk6_ppp_pppoe.ae9', {target: 'ti.targets.arm.elf.Arm9', suffix: 'e9'}],\n");
            sb.append("['lib/stk_ppp.ae9', {target: 'ti.targets.arm.elf.Arm9', suffix: 'e9'}],\n");
            sb.append("['lib/stk6_ppp.ae9', {target: 'ti.targets.arm.elf.Arm9', suffix: 'e9'}],\n");
            sb.append("['lib/stk_nat.ae9', {target: 'ti.targets.arm.elf.Arm9', suffix: 'e9'}],\n");
            sb.append("['lib/stk6_nat.ae9', {target: 'ti.targets.arm.elf.Arm9', suffix: 'e9'}],\n");
            sb.append("['lib/stk_nat_ppp.ae9', {target: 'ti.targets.arm.elf.Arm9', suffix: 'e9'}],\n");
            sb.append("['lib/stk6_nat_ppp.ae9', {target: 'ti.targets.arm.elf.Arm9', suffix: 'e9'}],\n");
            sb.append("['lib/stk_nat_ppp_pppoe.ae9', {target: 'ti.targets.arm.elf.Arm9', suffix: 'e9'}],\n");
            sb.append("['lib/stk6_nat_ppp_pppoe.ae9', {target: 'ti.targets.arm.elf.Arm9', suffix: 'e9'}],\n");
            sb.append("['lib/stk.aea8f', {target: 'ti.targets.arm.elf.A8F', suffix: 'ea8f'}],\n");
            sb.append("['lib/stk6.aea8f', {target: 'ti.targets.arm.elf.A8F', suffix: 'ea8f'}],\n");
            sb.append("['lib/stk_ppp_pppoe.aea8f', {target: 'ti.targets.arm.elf.A8F', suffix: 'ea8f'}],\n");
            sb.append("['lib/stk6_ppp_pppoe.aea8f', {target: 'ti.targets.arm.elf.A8F', suffix: 'ea8f'}],\n");
            sb.append("['lib/stk_ppp.aea8f', {target: 'ti.targets.arm.elf.A8F', suffix: 'ea8f'}],\n");
            sb.append("['lib/stk6_ppp.aea8f', {target: 'ti.targets.arm.elf.A8F', suffix: 'ea8f'}],\n");
            sb.append("['lib/stk_nat.aea8f', {target: 'ti.targets.arm.elf.A8F', suffix: 'ea8f'}],\n");
            sb.append("['lib/stk6_nat.aea8f', {target: 'ti.targets.arm.elf.A8F', suffix: 'ea8f'}],\n");
            sb.append("['lib/stk_nat_ppp.aea8f', {target: 'ti.targets.arm.elf.A8F', suffix: 'ea8f'}],\n");
            sb.append("['lib/stk6_nat_ppp.aea8f', {target: 'ti.targets.arm.elf.A8F', suffix: 'ea8f'}],\n");
            sb.append("['lib/stk_nat_ppp_pppoe.aea8f', {target: 'ti.targets.arm.elf.A8F', suffix: 'ea8f'}],\n");
            sb.append("['lib/stk6_nat_ppp_pppoe.aea8f', {target: 'ti.targets.arm.elf.A8F', suffix: 'ea8f'}],\n");
            sb.append("['lib/stk.aea8fnv', {target: 'ti.targets.arm.elf.A8Fnv', suffix: 'ea8fnv'}],\n");
            sb.append("['lib/stk6.aea8fnv', {target: 'ti.targets.arm.elf.A8Fnv', suffix: 'ea8fnv'}],\n");
            sb.append("['lib/stk_ppp_pppoe.aea8fnv', {target: 'ti.targets.arm.elf.A8Fnv', suffix: 'ea8fnv'}],\n");
            sb.append("['lib/stk6_ppp_pppoe.aea8fnv', {target: 'ti.targets.arm.elf.A8Fnv', suffix: 'ea8fnv'}],\n");
            sb.append("['lib/stk_ppp.aea8fnv', {target: 'ti.targets.arm.elf.A8Fnv', suffix: 'ea8fnv'}],\n");
            sb.append("['lib/stk6_ppp.aea8fnv', {target: 'ti.targets.arm.elf.A8Fnv', suffix: 'ea8fnv'}],\n");
            sb.append("['lib/stk_nat.aea8fnv', {target: 'ti.targets.arm.elf.A8Fnv', suffix: 'ea8fnv'}],\n");
            sb.append("['lib/stk6_nat.aea8fnv', {target: 'ti.targets.arm.elf.A8Fnv', suffix: 'ea8fnv'}],\n");
            sb.append("['lib/stk_nat_ppp.aea8fnv', {target: 'ti.targets.arm.elf.A8Fnv', suffix: 'ea8fnv'}],\n");
            sb.append("['lib/stk6_nat_ppp.aea8fnv', {target: 'ti.targets.arm.elf.A8Fnv', suffix: 'ea8fnv'}],\n");
            sb.append("['lib/stk_nat_ppp_pppoe.aea8fnv', {target: 'ti.targets.arm.elf.A8Fnv', suffix: 'ea8fnv'}],\n");
            sb.append("['lib/stk6_nat_ppp_pppoe.aea8fnv', {target: 'ti.targets.arm.elf.A8Fnv', suffix: 'ea8fnv'}],\n");
            sb.append("['lib/stk.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/stk6.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/stk_ppp_pppoe.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/stk6_ppp_pppoe.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/stk_ppp.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/stk6_ppp.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/stk_nat.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/stk6_nat.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/stk_nat_ppp.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/stk6_nat_ppp.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/stk_nat_ppp_pppoe.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/stk6_nat_ppp_pppoe.aem3', {target: 'ti.targets.arm.elf.M3', suffix: 'em3'}],\n");
            sb.append("['lib/stk.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/stk6.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/stk_ppp_pppoe.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/stk6_ppp_pppoe.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/stk_ppp.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/stk6_ppp.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/stk_nat.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/stk6_nat.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/stk_nat_ppp.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/stk6_nat_ppp.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/stk_nat_ppp_pppoe.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/stk6_nat_ppp_pppoe.aem4', {target: 'ti.targets.arm.elf.M4', suffix: 'em4'}],\n");
            sb.append("['lib/stk.aem4f', {target: 'ti.targets.arm.elf.M4F', suffix: 'em4f'}],\n");
            sb.append("['lib/stk6.aem4f', {target: 'ti.targets.arm.elf.M4F', suffix: 'em4f'}],\n");
            sb.append("['lib/stk_ppp_pppoe.aem4f', {target: 'ti.targets.arm.elf.M4F', suffix: 'em4f'}],\n");
            sb.append("['lib/stk6_ppp_pppoe.aem4f', {target: 'ti.targets.arm.elf.M4F', suffix: 'em4f'}],\n");
            sb.append("['lib/stk_ppp.aem4f', {target: 'ti.targets.arm.elf.M4F', suffix: 'em4f'}],\n");
            sb.append("['lib/stk6_ppp.aem4f', {target: 'ti.targets.arm.elf.M4F', suffix: 'em4f'}],\n");
            sb.append("['lib/stk_nat.aem4f', {target: 'ti.targets.arm.elf.M4F', suffix: 'em4f'}],\n");
            sb.append("['lib/stk6_nat.aem4f', {target: 'ti.targets.arm.elf.M4F', suffix: 'em4f'}],\n");
            sb.append("['lib/stk_nat_ppp.aem4f', {target: 'ti.targets.arm.elf.M4F', suffix: 'em4f'}],\n");
            sb.append("['lib/stk6_nat_ppp.aem4f', {target: 'ti.targets.arm.elf.M4F', suffix: 'em4f'}],\n");
            sb.append("['lib/stk_nat_ppp_pppoe.aem4f', {target: 'ti.targets.arm.elf.M4F', suffix: 'em4f'}],\n");
            sb.append("['lib/stk6_nat_ppp_pppoe.aem4f', {target: 'ti.targets.arm.elf.M4F', suffix: 'em4f'}],\n");
            sb.append("['lib/stk.am3g', {target: 'gnu.targets.arm.M3', suffix: 'm3g'}],\n");
            sb.append("['lib/stk6.am3g', {target: 'gnu.targets.arm.M3', suffix: 'm3g'}],\n");
            sb.append("['lib/stk_ppp_pppoe.am3g', {target: 'gnu.targets.arm.M3', suffix: 'm3g'}],\n");
            sb.append("['lib/stk6_ppp_pppoe.am3g', {target: 'gnu.targets.arm.M3', suffix: 'm3g'}],\n");
            sb.append("['lib/stk_ppp.am3g', {target: 'gnu.targets.arm.M3', suffix: 'm3g'}],\n");
            sb.append("['lib/stk6_ppp.am3g', {target: 'gnu.targets.arm.M3', suffix: 'm3g'}],\n");
            sb.append("['lib/stk_nat.am3g', {target: 'gnu.targets.arm.M3', suffix: 'm3g'}],\n");
            sb.append("['lib/stk6_nat.am3g', {target: 'gnu.targets.arm.M3', suffix: 'm3g'}],\n");
            sb.append("['lib/stk_nat_ppp.am3g', {target: 'gnu.targets.arm.M3', suffix: 'm3g'}],\n");
            sb.append("['lib/stk6_nat_ppp.am3g', {target: 'gnu.targets.arm.M3', suffix: 'm3g'}],\n");
            sb.append("['lib/stk_nat_ppp_pppoe.am3g', {target: 'gnu.targets.arm.M3', suffix: 'm3g'}],\n");
            sb.append("['lib/stk6_nat_ppp_pppoe.am3g', {target: 'gnu.targets.arm.M3', suffix: 'm3g'}],\n");
            sb.append("['lib/stk.am4g', {target: 'gnu.targets.arm.M4', suffix: 'm4g'}],\n");
            sb.append("['lib/stk6.am4g', {target: 'gnu.targets.arm.M4', suffix: 'm4g'}],\n");
            sb.append("['lib/stk_ppp_pppoe.am4g', {target: 'gnu.targets.arm.M4', suffix: 'm4g'}],\n");
            sb.append("['lib/stk6_ppp_pppoe.am4g', {target: 'gnu.targets.arm.M4', suffix: 'm4g'}],\n");
            sb.append("['lib/stk_ppp.am4g', {target: 'gnu.targets.arm.M4', suffix: 'm4g'}],\n");
            sb.append("['lib/stk6_ppp.am4g', {target: 'gnu.targets.arm.M4', suffix: 'm4g'}],\n");
            sb.append("['lib/stk_nat.am4g', {target: 'gnu.targets.arm.M4', suffix: 'm4g'}],\n");
            sb.append("['lib/stk6_nat.am4g', {target: 'gnu.targets.arm.M4', suffix: 'm4g'}],\n");
            sb.append("['lib/stk_nat_ppp.am4g', {target: 'gnu.targets.arm.M4', suffix: 'm4g'}],\n");
            sb.append("['lib/stk6_nat_ppp.am4g', {target: 'gnu.targets.arm.M4', suffix: 'm4g'}],\n");
            sb.append("['lib/stk_nat_ppp_pppoe.am4g', {target: 'gnu.targets.arm.M4', suffix: 'm4g'}],\n");
            sb.append("['lib/stk6_nat_ppp_pppoe.am4g', {target: 'gnu.targets.arm.M4', suffix: 'm4g'}],\n");
            sb.append("['lib/stk.am4fg', {target: 'gnu.targets.arm.M4F', suffix: 'm4fg'}],\n");
            sb.append("['lib/stk6.am4fg', {target: 'gnu.targets.arm.M4F', suffix: 'm4fg'}],\n");
            sb.append("['lib/stk_ppp_pppoe.am4fg', {target: 'gnu.targets.arm.M4F', suffix: 'm4fg'}],\n");
            sb.append("['lib/stk6_ppp_pppoe.am4fg', {target: 'gnu.targets.arm.M4F', suffix: 'm4fg'}],\n");
            sb.append("['lib/stk_ppp.am4fg', {target: 'gnu.targets.arm.M4F', suffix: 'm4fg'}],\n");
            sb.append("['lib/stk6_ppp.am4fg', {target: 'gnu.targets.arm.M4F', suffix: 'm4fg'}],\n");
            sb.append("['lib/stk_nat.am4fg', {target: 'gnu.targets.arm.M4F', suffix: 'm4fg'}],\n");
            sb.append("['lib/stk6_nat.am4fg', {target: 'gnu.targets.arm.M4F', suffix: 'm4fg'}],\n");
            sb.append("['lib/stk_nat_ppp.am4fg', {target: 'gnu.targets.arm.M4F', suffix: 'm4fg'}],\n");
            sb.append("['lib/stk6_nat_ppp.am4fg', {target: 'gnu.targets.arm.M4F', suffix: 'm4fg'}],\n");
            sb.append("['lib/stk_nat_ppp_pppoe.am4fg', {target: 'gnu.targets.arm.M4F', suffix: 'm4fg'}],\n");
            sb.append("['lib/stk6_nat_ppp_pppoe.am4fg', {target: 'gnu.targets.arm.M4F', suffix: 'm4fg'}],\n");
            sb.append("['lib/stk.aa8fg', {target: 'gnu.targets.arm.A8F', suffix: 'a8fg'}],\n");
            sb.append("['lib/stk6.aa8fg', {target: 'gnu.targets.arm.A8F', suffix: 'a8fg'}],\n");
            sb.append("['lib/stk_ppp_pppoe.aa8fg', {target: 'gnu.targets.arm.A8F', suffix: 'a8fg'}],\n");
            sb.append("['lib/stk6_ppp_pppoe.aa8fg', {target: 'gnu.targets.arm.A8F', suffix: 'a8fg'}],\n");
            sb.append("['lib/stk_ppp.aa8fg', {target: 'gnu.targets.arm.A8F', suffix: 'a8fg'}],\n");
            sb.append("['lib/stk6_ppp.aa8fg', {target: 'gnu.targets.arm.A8F', suffix: 'a8fg'}],\n");
            sb.append("['lib/stk_nat.aa8fg', {target: 'gnu.targets.arm.A8F', suffix: 'a8fg'}],\n");
            sb.append("['lib/stk6_nat.aa8fg', {target: 'gnu.targets.arm.A8F', suffix: 'a8fg'}],\n");
            sb.append("['lib/stk_nat_ppp.aa8fg', {target: 'gnu.targets.arm.A8F', suffix: 'a8fg'}],\n");
            sb.append("['lib/stk6_nat_ppp.aa8fg', {target: 'gnu.targets.arm.A8F', suffix: 'a8fg'}],\n");
            sb.append("['lib/stk_nat_ppp_pppoe.aa8fg', {target: 'gnu.targets.arm.A8F', suffix: 'a8fg'}],\n");
            sb.append("['lib/stk6_nat_ppp_pppoe.aa8fg', {target: 'gnu.targets.arm.A8F', suffix: 'a8fg'}],\n");
            sb.append("['lib/stk.aa9fg', {target: 'gnu.targets.arm.A9F', suffix: 'a9fg'}],\n");
            sb.append("['lib/stk6.aa9fg', {target: 'gnu.targets.arm.A9F', suffix: 'a9fg'}],\n");
            sb.append("['lib/stk_ppp_pppoe.aa9fg', {target: 'gnu.targets.arm.A9F', suffix: 'a9fg'}],\n");
            sb.append("['lib/stk6_ppp_pppoe.aa9fg', {target: 'gnu.targets.arm.A9F', suffix: 'a9fg'}],\n");
            sb.append("['lib/stk_ppp.aa9fg', {target: 'gnu.targets.arm.A9F', suffix: 'a9fg'}],\n");
            sb.append("['lib/stk6_ppp.aa9fg', {target: 'gnu.targets.arm.A9F', suffix: 'a9fg'}],\n");
            sb.append("['lib/stk_nat.aa9fg', {target: 'gnu.targets.arm.A9F', suffix: 'a9fg'}],\n");
            sb.append("['lib/stk6_nat.aa9fg', {target: 'gnu.targets.arm.A9F', suffix: 'a9fg'}],\n");
            sb.append("['lib/stk_nat_ppp.aa9fg', {target: 'gnu.targets.arm.A9F', suffix: 'a9fg'}],\n");
            sb.append("['lib/stk6_nat_ppp.aa9fg', {target: 'gnu.targets.arm.A9F', suffix: 'a9fg'}],\n");
            sb.append("['lib/stk_nat_ppp_pppoe.aa9fg', {target: 'gnu.targets.arm.A9F', suffix: 'a9fg'}],\n");
            sb.append("['lib/stk6_nat_ppp_pppoe.aa9fg', {target: 'gnu.targets.arm.A9F', suffix: 'a9fg'}],\n");
            sb.append("['lib/stk.aa15fg', {target: 'gnu.targets.arm.A15F', suffix: 'a15fg'}],\n");
            sb.append("['lib/stk6.aa15fg', {target: 'gnu.targets.arm.A15F', suffix: 'a15fg'}],\n");
            sb.append("['lib/stk_ppp_pppoe.aa15fg', {target: 'gnu.targets.arm.A15F', suffix: 'a15fg'}],\n");
            sb.append("['lib/stk6_ppp_pppoe.aa15fg', {target: 'gnu.targets.arm.A15F', suffix: 'a15fg'}],\n");
            sb.append("['lib/stk_ppp.aa15fg', {target: 'gnu.targets.arm.A15F', suffix: 'a15fg'}],\n");
            sb.append("['lib/stk6_ppp.aa15fg', {target: 'gnu.targets.arm.A15F', suffix: 'a15fg'}],\n");
            sb.append("['lib/stk_nat.aa15fg', {target: 'gnu.targets.arm.A15F', suffix: 'a15fg'}],\n");
            sb.append("['lib/stk6_nat.aa15fg', {target: 'gnu.targets.arm.A15F', suffix: 'a15fg'}],\n");
            sb.append("['lib/stk_nat_ppp.aa15fg', {target: 'gnu.targets.arm.A15F', suffix: 'a15fg'}],\n");
            sb.append("['lib/stk6_nat_ppp.aa15fg', {target: 'gnu.targets.arm.A15F', suffix: 'a15fg'}],\n");
            sb.append("['lib/stk_nat_ppp_pppoe.aa15fg', {target: 'gnu.targets.arm.A15F', suffix: 'a15fg'}],\n");
            sb.append("['lib/stk6_nat_ppp_pppoe.aa15fg', {target: 'gnu.targets.arm.A15F', suffix: 'a15fg'}],\n");
            sb.append("['lib/stk.arm3', {target: 'iar.targets.arm.M3', suffix: 'rm3'}],\n");
            sb.append("['lib/stk6.arm3', {target: 'iar.targets.arm.M3', suffix: 'rm3'}],\n");
            sb.append("['lib/stk_ppp_pppoe.arm3', {target: 'iar.targets.arm.M3', suffix: 'rm3'}],\n");
            sb.append("['lib/stk6_ppp_pppoe.arm3', {target: 'iar.targets.arm.M3', suffix: 'rm3'}],\n");
            sb.append("['lib/stk_ppp.arm3', {target: 'iar.targets.arm.M3', suffix: 'rm3'}],\n");
            sb.append("['lib/stk6_ppp.arm3', {target: 'iar.targets.arm.M3', suffix: 'rm3'}],\n");
            sb.append("['lib/stk_nat.arm3', {target: 'iar.targets.arm.M3', suffix: 'rm3'}],\n");
            sb.append("['lib/stk6_nat.arm3', {target: 'iar.targets.arm.M3', suffix: 'rm3'}],\n");
            sb.append("['lib/stk_nat_ppp.arm3', {target: 'iar.targets.arm.M3', suffix: 'rm3'}],\n");
            sb.append("['lib/stk6_nat_ppp.arm3', {target: 'iar.targets.arm.M3', suffix: 'rm3'}],\n");
            sb.append("['lib/stk_nat_ppp_pppoe.arm3', {target: 'iar.targets.arm.M3', suffix: 'rm3'}],\n");
            sb.append("['lib/stk6_nat_ppp_pppoe.arm3', {target: 'iar.targets.arm.M3', suffix: 'rm3'}],\n");
            sb.append("['lib/stk.arm4', {target: 'iar.targets.arm.M4', suffix: 'rm4'}],\n");
            sb.append("['lib/stk6.arm4', {target: 'iar.targets.arm.M4', suffix: 'rm4'}],\n");
            sb.append("['lib/stk_ppp_pppoe.arm4', {target: 'iar.targets.arm.M4', suffix: 'rm4'}],\n");
            sb.append("['lib/stk6_ppp_pppoe.arm4', {target: 'iar.targets.arm.M4', suffix: 'rm4'}],\n");
            sb.append("['lib/stk_ppp.arm4', {target: 'iar.targets.arm.M4', suffix: 'rm4'}],\n");
            sb.append("['lib/stk6_ppp.arm4', {target: 'iar.targets.arm.M4', suffix: 'rm4'}],\n");
            sb.append("['lib/stk_nat.arm4', {target: 'iar.targets.arm.M4', suffix: 'rm4'}],\n");
            sb.append("['lib/stk6_nat.arm4', {target: 'iar.targets.arm.M4', suffix: 'rm4'}],\n");
            sb.append("['lib/stk_nat_ppp.arm4', {target: 'iar.targets.arm.M4', suffix: 'rm4'}],\n");
            sb.append("['lib/stk6_nat_ppp.arm4', {target: 'iar.targets.arm.M4', suffix: 'rm4'}],\n");
            sb.append("['lib/stk_nat_ppp_pppoe.arm4', {target: 'iar.targets.arm.M4', suffix: 'rm4'}],\n");
            sb.append("['lib/stk6_nat_ppp_pppoe.arm4', {target: 'iar.targets.arm.M4', suffix: 'rm4'}],\n");
            sb.append("['lib/stk.arm4f', {target: 'iar.targets.arm.M4F', suffix: 'rm4f'}],\n");
            sb.append("['lib/stk6.arm4f', {target: 'iar.targets.arm.M4F', suffix: 'rm4f'}],\n");
            sb.append("['lib/stk_ppp_pppoe.arm4f', {target: 'iar.targets.arm.M4F', suffix: 'rm4f'}],\n");
            sb.append("['lib/stk6_ppp_pppoe.arm4f', {target: 'iar.targets.arm.M4F', suffix: 'rm4f'}],\n");
            sb.append("['lib/stk_ppp.arm4f', {target: 'iar.targets.arm.M4F', suffix: 'rm4f'}],\n");
            sb.append("['lib/stk6_ppp.arm4f', {target: 'iar.targets.arm.M4F', suffix: 'rm4f'}],\n");
            sb.append("['lib/stk_nat.arm4f', {target: 'iar.targets.arm.M4F', suffix: 'rm4f'}],\n");
            sb.append("['lib/stk6_nat.arm4f', {target: 'iar.targets.arm.M4F', suffix: 'rm4f'}],\n");
            sb.append("['lib/stk_nat_ppp.arm4f', {target: 'iar.targets.arm.M4F', suffix: 'rm4f'}],\n");
            sb.append("['lib/stk6_nat_ppp.arm4f', {target: 'iar.targets.arm.M4F', suffix: 'rm4f'}],\n");
            sb.append("['lib/stk_nat_ppp_pppoe.arm4f', {target: 'iar.targets.arm.M4F', suffix: 'rm4f'}],\n");
            sb.append("['lib/stk6_nat_ppp_pppoe.arm4f', {target: 'iar.targets.arm.M4F', suffix: 'rm4f'}],\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("init", pkgV);
        ((Value.Arr)om.findStrict("$packages", "ti.ndk.stack")).add(pkgV);
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
        if (isROV) {
        }//isROV
        $$SINGLETONS();
        $$INITIALIZATION();
    }
}