/**
 * Created by Victor on 30.03.2015.
 */
/**
 * Created by Victor on 28.03.2015.
 */
define(function () {

    var me;
    var container, camera, scene, renderer, objects, controls;
    var arduino, group;

    function Controller3D(debugWriter, sprintf) {
        me = this;
        me.debugWriter = debugWriter;
        me.sprintf = sprintf;

        if (!(this instanceof Controller3D)) {
            throw new TypeError("Controller3D constructor cannot be called as a function.");
        }
    }

    Controller3D.prototype = {
        constructor: Controller3D,
        start: function() {
            var loader = new THREE.ColladaLoader();
            loader.options.convertUpAxis = true;
            loader.load( './arduino.dae', function (collada) {
                arduino = collada.scene;
                arduino.scale.x = arduino.scale.y = arduino.scale.z = 3;
                arduino.updateMatrix();
                init();
                animate();
            });
        }
    };

    function init() {
        container = document.getElementById("container3d");
        scene = new THREE.Scene();
        renderer = new THREE.WebGLRenderer();
        renderer.setSize(container.offsetWidth, container.offsetHeight);
        container.appendChild(renderer.domElement);

        // objects
        group = new THREE.Object3D();//create an empty container
        group.add( arduino);//add a mesh with geometry to it
        scene.add( group );

        // Mark axes
        var geometryX = new THREE.BoxGeometry(10, 10, 10 );
        var materialX = new THREE.MeshBasicMaterial( { color: git0xff0000 } );
        var cubeX = new THREE.Mesh( geometryX, materialX );
        cubeX.position.x = 200;
        group.add( cubeX );

        var geometryY = new THREE.BoxGeometry(10, 10, 10 );
        var materialY = new THREE.MeshBasicMaterial( { color: 0x00ff00 } );
        var cubeY = new THREE.Mesh( geometryY, materialY );
        cubeY.position.y = 200;
        group.add( cubeY );

        var geometryZ = new THREE.BoxGeometry(10, 10, 10 );
        var materialZ = new THREE.MeshBasicMaterial( { color: 0x0000ff } );
        var cubeZ = new THREE.Mesh( geometryZ, materialZ );
        cubeZ.position.z = 200;
        group.add( cubeZ );


        // Lights
        var directionalLight = new THREE.DirectionalLight( 0xffffff, 1 );
        directionalLight.position.set( -1, 1, 1 );
        scene.add( directionalLight );

        var directionalLight2 = new THREE.DirectionalLight( 0xffffff, 0.2 );
        directionalLight2.position.set( 0, -1, 0 );
        scene.add( directionalLight2 );

        var directionalLight3 = new THREE.DirectionalLight( 0xffffff, 0.3 );
        directionalLight3.position.set( 1, 1, 0 );
        scene.add( directionalLight3 );

        // Camera
        camera = new THREE.OrthographicCamera( -250, 250, 250, -250, 1, 1000 );

        // Browser orientation controls
        controls = new DeviceOrientationController( camera, renderer.domElement );
        controls.connect();
    }

    function animate() {
        controls.update();

        var vector =   new THREE.Vector3(0, 0, -300);
        var m = camera.matrixWorld;
        vector.applyMatrix4(m);

        group.position.x = vector.x;
        group.position.y = vector.y;
        group.position.z = vector.z;

        requestAnimationFrame(animate);
        render();
    }

    function render() {
        //showCameraMatrix(camera);
        renderer.render(scene, camera);
    }

    function showCameraMatrix(camera)
    {
        var matrix = camera.matrixWorldInverse;

        var s = "";

        var p = sprintf("%.3f %.3f %.3f", camera.position.x, camera.position.y,camera.position.z);
        me.debugWriter.show("p", p);

        var a = sprintf("%.3f %.3f %.3f", arduino.position.x, arduino.position.y,arduino.position.z);
        me.debugWriter.show("a", a);

        try {
            for (var i = 0; i < 16; i++)
            {
                s += me.sprintf("%.3f", matrix.elements[i]);
                if (i%4 == 3)
                {
                    me.debugWriter.show("m" + i / 4, s);
                    s = "";
                }
                else
                {
                    s += " ";
                }
            }
        }
        catch(err)
        {
            toastr.error(err);
        }
    }

    return Controller3D;
});