var root = "";

function renderListing(listing,parent){
	if($.trim(listing).length > 0){
		//console.log(parent.children());
		var listArr = listing.split(",");
		var appendStr = "";
		for(var i=0;i<listArr.length;i++){
			if(i == 0){
				appendStr += "<ul val='"+ parent.text()+"'>";
			}
			
			appendStr += "<li>" + listArr[i] + "</li>";
			
			if(i == listArr.length-1){
				appendStr += "</ul>";
			}
		}
		
		//console.log(appendStr);
		parent.append(appendStr);
	}
}

function getListing(path,parent){
	console.log(path);
	$.ajax({
        type:"POST",
        url: "http://localhost:8888",
        data: {list:path},
        success: function(listings){
        	//console.log(data);
        	renderListing(listings,parent);
        }
      });
}

$(document).ready(function(){
	$("#get").click(function(){
		var path = $("#path").val();
		
		var parent = $("#listings");
		
		if(path.charAt(path.length - 1) == '\\'){
			path = path.slice(0, -1);
		}
		
		root = path;
		parent.empty();
		getListing(path,parent);
	});
	
	$("#root").click(function(){
		var parent = $("#listings");
		parent.empty();
		getListing(root,parent);
	});

	$("#listings").on("click", "li", function(e){
		if(e.target == this){
			//console.log($(this).has("ul"));
			if($(this).children().length > 0){
				$(this).find("ul").remove();
			}
			else{
				var newPath = "";
				if($(this).parent().attr("val") == ""){
					newPath = root + '\\' + $(this).text().trim();
				}
				else{
					var parent = $(this);
					newPath = $(this).text().trim();
					while(parent.parent().attr("val") != ""){
						//console.log(parent.parent().attr("val"));
						newPath = parent.parent().attr("val").trim() + '\\' + newPath;
					 	parent = parent.parent().parent();
					}
					
					newPath = root + '\\' + newPath;
				}
				//console.log($(this).parent().attr("val"));
				//console.log(newPath);
				getListing(newPath,$(this));
			}
		}
	});
});
