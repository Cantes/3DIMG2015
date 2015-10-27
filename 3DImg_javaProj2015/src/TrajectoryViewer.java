import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;

import ij.IJ;
import ij.ImagePlus;
import ij.plugin.filter.Rotator;
import ij.process.StackConverter;
import ij3d.Content;
import ij3d.Image3DUniverse;
import javafx.scene.transform.*;

public class TrajectoryViewer {

	public static void main(String[] args) {
		String dir = "D:/git/3DIMG2015/3DImg_javaProj2015";
		String file = "cochlee_resample.img";
		String path = dir + "/"+file;
		ImagePlus imp = tryPlugIn("Nifti_Reader",path);
	    
		new StackConverter(imp).convertToGray8();
		JFrame fr = new JFrame();

		fr.getContentPane().add(new JLabel(new ImageIcon(imp.getBufferedImage())));
		fr.setVisible(true);
		/*
		Image3DUniverse univ = new Image3DUniverse();
		univ.show();
		Content c = univ.addVoltex(imp);*/
		//IJ.runPlugIn("Volume Viewer","display_mode=4 scale=1 axes=0 interpolation=2 angle_x=0 angle_z=0 angle_y=80");
		imp.setSlice(10);
		JFrame fr2 = new JFrame();
		Rotator rotator = new Rotator();

		imp.getProcessor().rotate(20);
		
		fr2.getContentPane().add(new JLabel(new ImageIcon(imp.getBufferedImage())));
		fr2.setVisible(true);
	}
	
	private static ImagePlus tryPlugIn(String className, String path) {
		Object o = IJ.runPlugIn(className, path);
		ImagePlus imp = (ImagePlus)o;
		return imp;
	}

}