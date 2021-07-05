Epaisseur = 5;
Longueur = 100;
Largeur = 70;
Hauteur = 40;
HauteurCouvercle = 10;
AngleCoin = 10;

TailleTrou = 6.4;
NbTrou = 5;

DiameterAngle = 2 * AngleCoin;
Definition = 200;

Police = str("webdings");

// Principale
difference() {
  minkowski() {
    cube(size=[Largeur - DiameterAngle, Longueur - DiameterAngle, Hauteur]);
    cylinder(r = AngleCoin, h = 0.01, $fn = Definition);
  }
  union() {
    translate([Epaisseur / 2, Epaisseur / 2, Epaisseur]) {
      minkowski() {
        cube(size=[Largeur - DiameterAngle - Epaisseur, Longueur - DiameterAngle - Epaisseur, Hauteur]);
        cylinder(r = AngleCoin, h = 0.01, $fn = Definition);
      }
    }
    // previous
    for(i = [0 : 1 : NbTrou - 1]) {
      translate([Largeur - AngleCoin - TailleTrou / 2, 2 * i * (Longueur - DiameterAngle + TailleTrou / 2)/ (NbTrou * 2), Hauteur / 2 - TailleTrou / 2]) cube([TailleTrou, TailleTrou , TailleTrou]);
    }
    translate([Largeur - AngleCoin - TailleTrou / 2, 7/2 + 2 * 0 * (Longueur - DiameterAngle + TailleTrou / 2)/ (NbTrou * 2), Hauteur / 2 - TailleTrou / 2 + TailleTrou + 5]) rotate([90, 0, 90]) linear_extrude(5) text(text = "9", font = Police, size = 7, halign = "center", valign="center");
    // pause
    translate([Largeur - AngleCoin - TailleTrou / 2, 7/2 + 2 * 1 * (Longueur - DiameterAngle + TailleTrou / 2)/ (NbTrou * 2), Hauteur / 2 - TailleTrou / 2 + TailleTrou + 5]) rotate([90, 0, 90]) linear_extrude(5) text(text = ";", font = Police, size = 7, halign = "center", valign="center");
    // next
    translate([Largeur - AngleCoin - TailleTrou / 2, 7/2 + 2 * 2 * (Longueur - DiameterAngle + TailleTrou / 2)/ (NbTrou * 2), Hauteur / 2 - TailleTrou / 2 + TailleTrou + 5]) rotate([90, 0, 90]) linear_extrude(5) text(text = ":", font = Police, size = 7, halign = "center", valign="center");
    // vol down
    translate([Largeur - AngleCoin - TailleTrou / 2, 7/2 + 2 * 3 * (Longueur - DiameterAngle + TailleTrou / 2)/ (NbTrou * 2), Hauteur / 2 - TailleTrou / 2 + TailleTrou + 5]) rotate([90, 0, 90]) linear_extrude(5) text(text = "6", font = Police, size = 7, halign = "center", valign="center");
    // vol up
    translate([Largeur - AngleCoin - TailleTrou / 2, 7/2 + 2 * 4 * (Longueur - DiameterAngle + TailleTrou / 2)/ (NbTrou * 2), Hauteur / 2 - TailleTrou / 2 + TailleTrou + 5]) rotate([90, 0, 90]) linear_extrude(5) text(text = "5", font = Police, size = 7, halign = "center", valign="center");
    // on/off button
    rotate([90, 0, 0]) translate([Largeur/2 - AngleCoin, Hauteur/2, -5]) cylinder(50, 8, 8);
    // oled
    translate([-15, Longueur/2 - AngleCoin - 27/2, Hauteur/2 - 10.5/2]) cube([10, 27, 10.5]);
  }
}

// Couvercle
translate([Longueur * 1.15, 0, 0]) {
  difference() {
    union() {
      minkowski() {
        cube(size=[Largeur - DiameterAngle, Longueur - DiameterAngle, Epaisseur]);
        cylinder(r = AngleCoin, h = 0.01, $fn = Definition);
      }
      difference() {
        translate([Epaisseur / 2, Epaisseur / 2, 0]) {
          minkowski() {
            cube(size=[Largeur - DiameterAngle - Epaisseur, Longueur - DiameterAngle - Epaisseur, HauteurCouvercle]);
            cylinder(r = AngleCoin, h = 0.01, $fn = Definition);
          }
        }
        translate([Epaisseur, Epaisseur, Epaisseur]) {
          minkowski() {
            cube(size=[Largeur - DiameterAngle - 2 * Epaisseur, Longueur - DiameterAngle - 2 * Epaisseur, Hauteur]);
            cylinder(r = AngleCoin, h = 0.01, $fn = Definition);
          }
        }
      }
    }
    union() {
      for(i = [0 : 5 : 15]) {
        for (j = [0 : 5 : 15]) {
          translate([i, j, 0]) cylinder(15, 2, 2);
        }
      }
      translate([Largeur - AngleCoin - TailleTrou / 2, 7/2 + 2 * 4 * (Longueur - DiameterAngle + TailleTrou / 2)/ (NbTrou * 2), Hauteur / 2 - TailleTrou / 2 + TailleTrou + 5]) rotate([90, 0, 90]) linear_extrude(5) text(text = "¯", font = Police, size = 7, halign = "center", valign="center");
    }
    translate([Longueur/4, Longueur/2, 0]) rotate([0,0,180]) linear_extrude(1) text(text = "¯", font = Police, size = 60, halign = "center", valign="center");
  }
}