// Card
width=95;
depth=65;
height=1.65;
//translate([0,0,1.65])cube([width,depth,height],center=true);



//Bottom box
boxwidth=95;
boxdepth=75;
boxheight=5;
difference(){
cube([boxwidth,boxdepth,boxheight],center=true);
translate([0,0,boxheight/2-1.75/2])cube([95+0.1,65,1.75],center=true);

translate([0,0,boxheight/2-3/2])cube([78,61,3],center=true);
//translate([0,0,boxheight/2-3/2])cylinder(20,1.5,center=true);
translate([0,0,boxheight/2-3/2])cylinder(20,1.5,center=true,$fn=6);
}

