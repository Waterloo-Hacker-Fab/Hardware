# Piezo Stage 

## Overview
This is an open source piezo stage build, heavily inspired by the following paper: https://www.sciencedirect.com/science/article/pii/S2468067222000621

Notes about the paper mentioned above: 
1. The paper provides a great schematic for a piezo driver PCB. However, some of the parts are obsolete, and the design is built on a perfboard.

2. The paper also includes CAD design files. However, the mechanical parts used in these designs are either difficult to source or obsolete. In our design, we decided to replace these hard-to-get parts with alternatives based on CMU’s current stage. The CAD files require no modification when used with the current BOM.
    


The goal of the PCB redesign was to: 
1. Remove obsolete components -  Easier to source parts and ensures long-term availability.

2. Remove perfboard design - Simplifies the assembly process.



The goal of the CAD redesign was to: 
1. Modular attachment system - Allows mounting the stage to various surfaces (e.g., metric/imperial optical breadboard).

2. Modular mounting surface - Enables testing of different wafer clamping systems.

3. Up-to-date 3D printable CAD files - No obsolete parts, uses current BOM

4. Provide a "standard" stage - Provide a "base" so people can build on top of (incorporating measurement systems or custom wafer clamps.).

5. Provide a cheaper alternative for building a piezo stage.

---

## Folder Structure

- **/CAD Design/**  
  Contains all the .sldprt/.sldasm/.stl files needed to print/modify for your needs.  
  <span style="color:red"> Note: Contains BOM for the piezo stage build ("MECH_piezo_stage_BOM.xlsx") </span>

- **/LTspice Simulation/**  
  Nitty gritty simulations of schematics (good for learning, useless for recreating the project).

- **/PCB Design/**  
  PCB design files (Gerber and drill files) for the XYZ Piezo Stage driver. Also comes with KiCAD files.  
  <span style="color:red"> Note: Contains BOM for the piezo stage PCB ("PCB_piezo_stage_BOM.csv") </span>

- **/Pictures/**  
  Pictures of the PCB and mechanical parts.

- **/Firmware/**  
  Coming soon.

---

## 3D Printing

- List of parts to print (Check "Printed Parts" folder):  
  - `XY_Base.SLDPRT` — Base frame for both X & Y stage (Print 2 for XY stage.)  
  - `XY_Plate.SLDPRT` — Top plate for both X & Y stage (Print 2 for XY stage.)
  - `Z_Base.SLDPRT` — Base frame for Z stage (print only 1 for XYZ stage.)  
  - `Z_Plate.SLDPRT` — Top plate for Z stage (print only 1 for XYZ stage.)
  - `Z_Cover.SLDPRT` — Side cover frame for Z stage (print only 1 for XYZ stage.)

  Optional:
  - `XY_Base_Connector_(Metric).SLDPRT` — Connector for mounting the stage to a metric optical breadboard (print only 1.)
  - `XY_Base_Connector_(Imperial).SLDPRT` — Coming soon.
  


- Printing recommendations:  
  - Material: PLA or ABS  
  - Layer height: 0.2 mm  
  - Infill: 20% (adjust for strength as needed)  
  - Supports: Required for all parts.

---