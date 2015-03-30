/**
 * Created by Victor on 30.03.2015.
 */
/**
 * Created by Victor on 28.03.2015.
 */
define(function () {

    var me;
    var container, camera, scene, renderer, objects, controls;
    var arduino;

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
        scene.add(arduino);

        /*
         var geometry = new THREE.BoxGeometry( 20, 20, 20 );
         var material = new THREE.MeshBasicMaterial( { color: 0x00ff00 } );
         var cube = new THREE.Mesh( geometry, material );
         cube.position.y = 100;
         scene.add( cube );
         */

        // create a point light
        var pointLight =
            new THREE.PointLight(0xFFFFFF);
        // set its position
        pointLight.position.x = 200;
        pointLight.position.y = 600;
        pointLight.position.z = 900;
        // add to the scene
        scene.add(pointLight);

        var ambientLight = new THREE.AmbientLight( 0x101010 ); // soft white light
        scene.add(ambientLight);

        camera = new THREE.OrthographicCamera( -250, 250, 250, -250, 1, 1000 );
        camera.position.z = 300;

        controls = new DeviceOrientationController( camera, renderer.domElement );
        controls.connect();
    }

    function animate() {
        controls.update();

        arduino.position.x = camera.position.x - camera.matrixWorldInverse.elements[12];
        arduino.position.y = camera.position.y - camera.matrixWorldInverse.elements[13];
        arduino.position.z = camera.position.z + camera.matrixWorldInverse.elements[14];

        requestAnimationFrame(animate);
        render();
    }

    function render() {

        var matrixWorldInverse = camera.matrixWorldInverse;
        var projectionMatrix = camera.projectionMatrix;

        showCameraMatrix(camera);

        /*
         if (arduino !== null)
         {
         arduino.rotation.x += 0.01;
         arduino.rotation.y += 0.01;
         }*/
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