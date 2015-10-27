package examples;

import ij.process.StackConverter;
import ij.plugin.PlugIn;
import ij.ImagePlus;
import ij.IJ;

import ij3d.Image3DUniverse;
import ij3d.Content;

public class Display_Content implements PlugIn {

	  public static void main(String[] args) {
		    new ij.ImageJ();
		    IJ.runPlugIn("ij3d.examples.Display_Content", "");
	  }

	  public void run(String arg) {

		    // Open an image
		    String path = "/home/bene/PhD/brains/template.tif";
		    ImagePlus imp = IJ.openImage(path);
		    new StackConverter(imp).convertToGray8();

		    // Create a universe and show it
		    Image3DUniverse univ = new Image3DUniverse();
		    univ.show();

		    // Add the image as a volume rendering
		    Content c = univ.addVoltex(imp);
		    sleep(5);

		    // Display the image as orthslices
		    c.displayAs(Content.ORTHO);
		    sleep(5);

		    // Remove the content
		    univ.removeContent(c.getName());
		    sleep(5);

		    // Add an isosurface
		    c = univ.addMesh(imp);
		    sleep(5);

		    // display slice 10 as a surface plot
		    univ.removeContent(c.getName());
		    imp.setSlice(10);
		    c = univ.addSurfacePlot(imp);
		    sleep(5);

		    // remove all contents
		    univ.removeAllContents();

		    // close
		    univ.close();
	  }

	  private static void sleep(int sec) {
		    try {
				Thread.sleep(sec * 1000);
		    } catch(InterruptedException e) {
				System.out.println(e.getMessage());
		    }
	  }
}
