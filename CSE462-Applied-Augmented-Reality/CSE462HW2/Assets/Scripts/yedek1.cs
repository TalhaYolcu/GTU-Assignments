
/*
    private void ransacTransform1() {
        bool break_flag=false;
        Point3D my_transform=new Point3D(0.0f,0.0f,0.0f);
        for(int i=0;i<blues.Count && !break_flag;i++) {
            for(int j=i+1;j<blues.Count && !break_flag;j++) {
                for(int k=j+1;k<blues.Count && !break_flag;k++) {
                    Point3D bp1=new Point3D(blues[i].transform.position.x,blues[i].transform.position.y,blues[i].transform.position.z);
                    Point3D bp2=new Point3D(blues[j].transform.position.x,blues[j].transform.position.y,blues[j].transform.position.z);
                    Point3D bp3=new Point3D(blues[k].transform.position.x,blues[k].transform.position.y,blues[k].transform.position.z);
                    for(int i2=0;i2<yellows.Count && !break_flag;i2++) {
                        for(int j2=i2+1;j2<yellows.Count && !break_flag;j2++) {
                            for(int k2=j2+1;k2<yellows.Count && !break_flag;k2++) {
                                Point3D yp1=new Point3D(yellows[i2].transform.position.x,yellows[i2].transform.position.y,yellows[i2].transform.position.z);
                                Point3D yp2=new Point3D(yellows[j2].transform.position.x,yellows[j2].transform.position.y,yellows[j2].transform.position.z);
                                Point3D yp3=new Point3D(yellows[k2].transform.position.x,yellows[k2].transform.position.y,yellows[k2].transform.position.z);
                                Point3D distance1=calculateDistance(bp1,yp1);
                                Point3D distance2=calculateDistance(bp1,yp2);
                                Point3D distance3=calculateDistance(bp1,yp3);
                                Point3D distance4=calculateDistance(bp2,yp1);
                                Point3D distance5=calculateDistance(bp2,yp2);
                                Point3D distance6=calculateDistance(bp2,yp3);
                                Point3D distance7=calculateDistance(bp3,yp1);
                                Point3D distance8=calculateDistance(bp3,yp2);
                                Point3D distance9=calculateDistance(bp3,yp3);
                                bool found_flag=false;
                                if(distance1.compare(distance5) && distance5.compare(distance9)) {
                                    found_flag=true;
                                    my_transform.x=distance1.x;
                                    my_transform.y=distance1.y;
                                    my_transform.z=distance1.z;
                                    
                                }
                                else if(distance1.compare(distance6) && distance6.compare(distance8)) {
                                    found_flag=true;
                                    my_transform.x=distance1.x;
                                    my_transform.y=distance1.y;
                                    my_transform.z=distance1.z;
                                }
                                else if(distance2.compare(distance4) && distance4.compare(distance9)) {
                                    found_flag=true;
                                    my_transform.x=distance2.x;
                                    my_transform.y=distance2.y;
                                    my_transform.z=distance2.z;                                    
                                }
                                else if(distance2.compare(distance6) && distance6.compare(distance7)) {
                                    found_flag=true;
                                    my_transform.x=distance2.x;
                                    my_transform.y=distance2.y;
                                    my_transform.z=distance2.z;                                    
                                }
                                else if(distance3.compare(distance4) && distance4.compare(distance8)) {
                                    found_flag=true;
                                    my_transform.x=distance3.x;
                                    my_transform.y=distance3.y;
                                    my_transform.z=distance3.z;                                    
                                }
                                else if(distance3.compare(distance5) && distance5.compare(distance7)) {
                                    found_flag=true;                                    
                                    my_transform.x=distance3.x;
                                    my_transform.y=distance3.y;
                                    my_transform.z=distance3.z;
                                }
                                if(found_flag) {
                                    print(yp1.z);
                                    print(yp2.z);
                                    print(yp3.z);

                                    print("Found");
                                    break_flag=true;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
        print(my_transform.x);
        print(my_transform.y);
        print(my_transform.z);
    }
    private void ransacTransformv2() {
        bool break_flag=false;
        Point3D my_transform=new Point3D(0.0f,0.0f,0.0f);
        double[,] final_rotation=new double[3,3];
        double[,] final_translation=new double[3,0];
        for(int i=0;i<blues.Count && !break_flag;i++) {
            for(int j=i+1;j<blues.Count && !break_flag;j++) {
                for(int k=j+1;k<blues.Count && !break_flag;k++) {
                    Point3D bp1=new Point3D(blues[i].transform.position.x,blues[i].transform.position.y,blues[i].transform.position.z);
                    Point3D bp2=new Point3D(blues[j].transform.position.x,blues[j].transform.position.y,blues[j].transform.position.z);
                    Point3D bp3=new Point3D(blues[k].transform.position.x,blues[k].transform.position.y,blues[k].transform.position.z);
                    for(int i2=0;i2<yellows.Count && !break_flag;i2++) {
                        for(int j2=i2+1;j2<yellows.Count && !break_flag;j2++) {
                            for(int k2=j2+1;k2<yellows.Count && !break_flag;k2++) {
                                
                                Point3D yp1=new Point3D(yellows[i2].transform.position.x,yellows[i2].transform.position.y,yellows[i2].transform.position.z);
                                Point3D yp2=new Point3D(yellows[j2].transform.position.x,yellows[j2].transform.position.y,yellows[j2].transform.position.z);
                                Point3D yp3=new Point3D(yellows[k2].transform.position.x,yellows[k2].transform.position.y,yellows[k2].transform.position.z);

                                Point3D blue_centroid=findCentroid(bp1,bp2,bp3);
                                Point3D yellow_centroid=findCentroid(yp1,yp2,yp3);

                                bp1=reCentrePoint(bp1,blue_centroid);
                                bp2=reCentrePoint(bp2,blue_centroid);
                                bp3=reCentrePoint(bp3,blue_centroid);

                                yp1=reCentrePoint(yp1,yellow_centroid);
                                yp2=reCentrePoint(yp2,yellow_centroid);
                                yp3=reCentrePoint(yp3,yellow_centroid);

                                double[,] matrixA=new double[3,3];
                                double[,] matrixB=new double[3,3];
                                double[,] centroidmatrixA=new double[3,1];
                                double[,] centroidmatrixB=new double[3,1];
                                double[,] matrixH=new double[3,3];


                                matrixA[0,0]=Convert.ToDouble(bp1.x);
                                matrixA[0,1]=Convert.ToDouble(bp2.x);
                                matrixA[0,2]=Convert.ToDouble(bp3.x);

                                matrixA[1,0]=Convert.ToDouble(bp1.y);
                                matrixA[1,1]=Convert.ToDouble(bp2.y);
                                matrixA[1,2]=Convert.ToDouble(bp3.y);

                                matrixA[2,0]=Convert.ToDouble(bp1.z);
                                matrixA[2,1]=Convert.ToDouble(bp2.z);
                                matrixA[2,2]=Convert.ToDouble(bp3.z);      

                                matrixB[0,0]=Convert.ToDouble(yp1.x);
                                matrixB[0,1]=Convert.ToDouble(yp2.x);
                                matrixB[0,2]=Convert.ToDouble(yp3.x);

                                matrixB[1,0]=Convert.ToDouble(yp1.y);
                                matrixB[1,1]=Convert.ToDouble(yp2.y);
                                matrixB[1,2]=Convert.ToDouble(yp3.y);

                                matrixB[2,0]=Convert.ToDouble(yp1.z);
                                matrixB[2,1]=Convert.ToDouble(yp2.z);
                                matrixB[2,2]=Convert.ToDouble(yp3.z); 

                                centroidmatrixA[0,0]=Convert.ToDouble(blue_centroid.x);
                                centroidmatrixA[1,0]=Convert.ToDouble(blue_centroid.y);
                                centroidmatrixA[2,0]=Convert.ToDouble(blue_centroid.z);

                                centroidmatrixB[0,0]=Convert.ToDouble(yellow_centroid.x);
                                centroidmatrixB[1,0]=Convert.ToDouble(yellow_centroid.y);
                                centroidmatrixB[2,0]=Convert.ToDouble(yellow_centroid.z);

                                double[,] subtractedmatrixA=subtractCentroid(matrixA,centroidmatrixA);      
                                double[,] subtractedmatrixB=subtractCentroid(matrixB,centroidmatrixB);

                                double[,] transponsesubtractedmatrixB=takeTransponse(subtractedmatrixB);

                                matrixH=matrixMultiply(subtractedmatrixA,transponsesubtractedmatrixB);

                                SingularValueDecomposition svd=new SingularValueDecomposition(matrixH);
                                
                                double[,] vmatrix=svd.RightSingularVectors;
                                double[,] umatrix=svd.LeftSingularVectors;

                                double[,] rotation=matrixMultiply(vmatrix,takeTransponse(umatrix));

                                if(matrixDet(rotation)<0) {
                                    svd=new SingularValueDecomposition(rotation);
                                    vmatrix=svd.RightSingularVectors;
                                    umatrix=svd.LeftSingularVectors;
                                    for(int mm=0;mm<3;mm++) {
                                        vmatrix[mm,0]=vmatrix[mm,0]*(-1.0);
                                    }
                                    rotation=matrixMultiply(vmatrix,takeTransponse(umatrix));
                                }
                                double [,]translation=findTranslation(rotation,centroidmatrixA,centroidmatrixB);
                                
                                //Debug.Log(rotation[0,0]+" "+rotation[0,1]+" "+rotation[0,2]+" "+tempmatrixB[0,0]+" "+tempmatrixB[0,1]+" "+tempmatrixB[0,2]);

                            }
                        }
                    }
                }
            }
        }  
        Debug.Log(final_rotation[0,0]+" "+final_rotation[0,1]+" "+final_rotation[0,2]+" "+final_rotation[1,0]+" "+final_rotation[1,1]+" "+final_rotation[1,2]);
    }

    */